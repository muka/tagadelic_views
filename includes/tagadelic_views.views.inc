<?php


/**
 * Implements hook_views_plugins().
 *
 * Defines some plugins used by the Views modes for
 * user_reference.
 */

function tagadelic_views_views_plugins() {
  
  $plugins = array(
//     'display' => array(
//       'tagadelic' => array(
//         'title' => t('Tagadelic'),
//         'admin' => t('Tagadelic'),
//         'help' => 'Shows Tagadelic terms',
//         'handler' => 'tagadelic_plugin_display_default',
//         'uses hook menu' => FALSE,
//         'use ajax' => FALSE,
//         'use pager' => FALSE,
//         'accept attachments' => FALSE,
//         // Custom property, used with views_get_applicable_views() to retrieve
//         // all views with a 'References' display.
// //         'references display' => TRUE,
//       ),
//     ),
    'style' => array(
      'tagadelic' => array(
        'title' => t('Tagadelic list'),
        'help' => t('Displays terms as tagadelic.'),
        'handler' => 'tagadelic_plugin_style',
        'parent' => 'list',
        'theme' => 'views_view_list',
//        'theme' => 'tagadelic_views_row',
//        'theme path' => drupal_get_path('module', 'tagadelic_views'),
//        'theme file' => 'tagadelic-views-row.tpl.php',        
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
//        'help topic' => 'style-list',
      ),      
    ),
//    'row' => array(
//      'tagadelic_fields' => array(
//        'title' => t('Tagadelic terms'),
//        'help' => t('Displays tagadelic terms.'),
//        'handler' => 'tagadelic_plugin_row_fields',
//        'parent'  => 'fields',
//        'theme' => 'views_view_fields',
////        'theme' => 'tagadelic_weighted',
////        'theme path' => drupal_get_path('module', 'tagadelic_views'),
////        'theme file' => 'tagadelic_views_weighted.tpl.php',
//        'uses fields' => TRUE,
//        'uses options' => TRUE,
//        'type' => 'normal',
//      ),
//    ),    
  );
  return $plugins;
}