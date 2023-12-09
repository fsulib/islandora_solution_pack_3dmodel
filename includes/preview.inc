<?php

/**
 * @file
 * 3D object preview page upload form.
 */

function islandora_3dmodel_preview_upload_form() {
  $form = array();
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('Upload 3D Model Object File'),
    '#description' => t('Upload a 3D model object file, allowed extensions: obj, 3ds, stl, ply, gltf, glb, 3dm, fbx, off'),
  );
  $form['captcha'] = array(
    '#type' => 'captcha',
  );
  $form['text']['#markup'] = '<p><strong>Warning!</strong> Files uploaded through this preview will be publicly accessible, and will be regularly deleted.</p>';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Upload',
  );
  return $form;
}

function islandora_3dmodel_preview_upload_form_validate($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('obj 3ds stl ply gltf glb 3dm fbx off'));
  $directory = "public://3dmodel_object_preview";
  file_prepare_directory($directory, $options = FILE_CREATE_DIRECTORY);
  $file = file_save_upload('file', $validators, $directory);
  if (!$file) {
    form_set_error('file', t('No file was uploaded.'));
  }
}

function islandora_3dmodel_preview_upload_form_submit($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('obj 3ds stl ply gltf glb 3dm fbx off'));
  $directory = "public://3dmodel_object_preview";
  file_prepare_directory($directory, $options = FILE_CREATE_DIRECTORY);
  $file = file_save_upload('file', $validators, $directory);

  $form_state['redirect'] = array('/islandora/previews/3dmodel/view', array('query' => array('file' => $file->filename)));
}

function islandora_3dmodel_preview_display() {
  drupal_add_js(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/libs/pickr.monolith.min.css');
  drupal_add_js(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/libs/pickr.es5.min.js');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/icons.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/themes.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/core.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/controls.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/dialogs.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/treeview.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/panelset.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/navigator.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/sidebar.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/website.css');
  drupal_add_css(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/css/embed.css');
  drupal_add_js(drupal_get_path('module', 'islandora_3dmodel') .'/o3dv/o3dv.website.min.js');


  global $base_url;
  $file_name = escapeshellcmd($_GET['file']);
  $full_path = drupal_realpath("public://3dmodel_object_preview");
  $route = str_replace('/var/www/html', '', $full_path);
  $iframepath = drupal_get_path('module', 'islandora_3dmodel') . '/o3dv/viewer.html';

  $output = <<<END
<iframe src="{$base_url}/{$iframepath}#model={$route}/{$file_name}" style="width: 100%; min-height: 50em; padding-bottom: 1em;" title="Online 3D Viewer Window"></iframe>
END;

  return $output;
}
