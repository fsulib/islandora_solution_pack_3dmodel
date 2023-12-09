<?php

/**
 * @file
 * Defines the 3D model import classes.
 */

/**
 * 3D Model Zip Importer.
 */
class _3dModelZipBatchImporter extends ZipBatchImporter {

  protected $itemClass = '_3dModelZipBatchImportObject';

  /**
   * Get the form for this importer.
   *
   * @see IslandoraBatchImporter::getForm()
   */
  public static function getForm(array &$form_state) {
    $parent = islandora_object_load($form_state['storage']['parent_pid']);
    $ns_options = array(
      NULL => t('Default namespace'),
    );
    $policy = new CollectionPolicy($parent['COLLECTION_POLICY']->content);
    $models = $policy->getContentModels();
    $namespace = $models['islandora:3dModelCModel']['namespace'];
    if (!empty($namespace)) {
      module_load_include('inc', 'islandora', 'includes/utilities');
      $namespace = islandora_get_namespace($namespace);
      $ns_options[$namespace] = $namespace;
    }

    return array(
      'fs' => array(
        '#type' => 'fieldset',
        '#title' => t('3D Model Zip Batch Importer'),
        '#description' => t('TBD'),
        'file' => array(
          '#type' => 'managed_file',
          '#title' => t('Zip file containing files to import'),
          '#upload_validators' => array(
            'file_validate_extensions' => array('zip'),
          ),
        ),
        'namespace' => array(
          '#type' => 'select',
          '#title' => t('Object Namespace'),
          '#description' => t('The namespace in which the imported objects will be created.'),
          '#options' => $ns_options,
        ),
        'submit' => array(
          '#type' => 'submit',
          '#value' => t('Import'),
        ),
      ),
    );
  }

  /**
   * Determine if we're ready to process the batch.
   *
   * @see IslandoraBatchImporter::readyForBatch()
   */
  public static function readyForBatch(array &$form_state) {
    if (empty($form_state['values']['file'])) {
      form_set_error('file', t('Need a Zip file!'));
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Get info for the source parameter for the itemClass factory.
   *
   * @see IslandoraBatchImporterInterface::getBatchInfo()
   */
  public static function getBatchInfo(array &$form_state) {
    $file = is_object($form_state['values']['file']) ? $form_state['values']['file'] : file_load($form_state['values']['file']);
    $zip = new ZipArchive();
    if (($error = $zip->open(drupal_realpath($file->uri))) !== TRUE) {
      drupal_set_message(t('Error opening the provided Zip file.  Code: %code', array(
            '%code' => $error,
          )));
      return;
    }
    $dsmap_content = $zip->getFromName('dsmap.json');
    $zip->close();

    $dsmap = json_decode($dsmap_content, TRUE);
    $object_key = '.-_-' . pathinfo(array_search('MF0', $dsmap))['filename'];

    $custom_object_info = array(); 
    $custom_object_info[$object_key]['DSMAP'] = 'dsmap.json';
    foreach ($dsmap as $filename => $dsid) {
      $custom_object_info[$object_key][$dsid] = $filename;
    }

    return array(
      'file' => $file,
      'pid_namespace' => $form_state['values']['namespace'],
      'object_info' => $custom_object_info,
      'processed_objects' => array(),
    );
  }

}

/**
 * Zip import binary object.
 */
class _3dModelZipBatchImportObject extends ZipBatchImportObject {

  public function getTitle() {
    $mods_file = $this->source['object_info']['MODS'];
    $zip = new ZipArchive();
    $zip->open(drupal_realpath($this->source['file']->uri));
    $mods_content = $zip->getFromName($mods_file);
    $zip->close();
    $mods_doc = new DOMDocument();
    $mods_doc->loadXML($mods_content);
    $mods_xpath = new DOMXPath($mods_doc);
    $mods_xpath->registerNamespace('m', 'http://www.loc.gov/mods/v3');
    $this->title = $mods_xpath->evaluate('string(//m:mods/m:titleInfo/m:title/text())');
    return $this->title;
  }

  /**
   * Get an item from the source.
   *
   * @see IslandoraImportObjectInterface::getOne()
   */
  public static function getOne(&$info) {
    $key = key($info['object_info']);
    if (count($info['object_info'][$key]) == 1 && isset($info['object_info'][$key]['xml'])) {
      unset($info['object_info'][$key]);
      return FALSE;
    }
    $record = array(
      'pid_namespace' => $info['pid_namespace'],
      'file' => $info['file'],
      'content_model' => array('islandora:3dModelCModel'),
    );
    $record['object_info'] = $info['processed_objects'][$key] = $info['object_info'][$key];
    unset($info['object_info'][$key]);
    return (empty($record) ? FALSE : new static($record));
  }

  protected function determineMimetype($name) {
    static $mime_detect = NULL;
    if (is_null($mime_detect)) {
      $mime_detect = new MimeDetect();
    }
    return $mime_detect->getMimetype($name);
  }

  /**
   * Get the datastream structure for an object.
   *
   * @see IslandoraImportObject::getDatastreams()
   */
  protected function getDatastreams(&$errors = NULL, &$files = NULL) {
    $to_return = array();
    $default_scheme = file_default_scheme() . "://";
    module_load_include('inc', 'islandora', 'includes/utilities');

    // Get DSID and mimetype.
    foreach ($this->source['object_info'] as $datastream => $name) {
      $mimetype = $this->determineMimetype($name);
      $zip = new ZipArchive();
      $zip->open(drupal_realpath($this->source['file']->uri));
      if ($stream = $zip->getStream($name)) {
        $uri = file_unmanaged_save_data($stream, $default_scheme . basename($name));
        $file = islandora_temp_file_entry($uri, $mimetype);
        $files[] = $file;
        $to_return += array(
          $datastream => array(
            'dsid' => $datastream,
            'label' => "$name",
            'mimetype' => $mimetype,
            'datastream_file' => file_create_url($file->uri),
            'filename' => $name,
            'control_group' => 'M',
            'file' => $file,
          ),
        );
      }
      $zip->close();
    }
    return $to_return;
  }
}
