<?php

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


$dsmap = json_decode($islandora_object['DSMAP']->content, TRUE);
$models_string = '';
$datastream_route_base = "/islandora/object/{$islandora_object->id}/modelfile/";
$i = 0;
foreach ($dsmap as $filename => $datastream) {
  if ($datastream != "MODS") {
    if ($i == 0) {
      $separator = '';
    }
    else {
      $separator = ',';
    }
    $models_string .= $separator . $datastream_route_base . $filename;
    $i++;
  }
}
$iframepath = drupal_get_path('module', 'islandora_3dmodel') . '/o3dv/viewer.html';
$output = "<iframe src='/{$iframepath}#model={$models_string}' style='width:100%; min-height: 40em; padding-bottom: 1em;' title='Online 3D Viewer Window'></iframe>";
?>

<div class="islandora-3dmodel-object islandora-object islandora">

  <div class="islandora-3dmodel-content-wrapper islandora-3dmodel-viewer clearfix">
  <?php print $output; ?>
  </div>

</div>
