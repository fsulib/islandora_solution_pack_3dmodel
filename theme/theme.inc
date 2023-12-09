<?php

/**
 * @file
 * Handles the display of 3D models.
 */

/**
 * Implements hook_preprocess_theme().
 */
function template_preprocess_islandora_3dmodel(array &$variables) {
  module_load_include('inc', 'islandora', 'includes/metadata');
  $islandora_object = $variables['islandora_object'];

  // Thumbnail.
  if (isset($islandora_object['TN']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $islandora_object['TN'])) {
    $thumbnail_size_url = url("islandora/object/{$islandora_object->id}/datastream/TN/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $thumbnail_size_url,
    );
    $variables['islandora_thumbnail_img'] = theme('image', $params);
  }
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($islandora_object);
  $variables['metadata'] = islandora_retrieve_metadata_markup($islandora_object);
  $variables['description'] = islandora_retrieve_description_markup($islandora_object);
}
