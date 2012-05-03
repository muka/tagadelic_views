<?php


/**
 * Implements hook_views_plugins().
 *
 * Defines some plugins used by the Views modes for
 * user_reference.
 */

function tagadelic_views_views_plugins() {
  
  $plugins = array(
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
        'uses row plugin' => 'tagadelic_plugin_row_fields',
        //'uses row class' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
//        'help topic' => 'style-list',
      ),      
    ),
  );
  return $plugins;
}


/**
 * Implementation of hook_views_query_alter
 */
function tagadelic_views_views_query_alter(&$view, &$query) {

  if(  get_class($view->style_plugin) != 'tagadelic_plugin_style')
  {
    return;
  }

  $field_tid = 'tid';
  $taxonomy_term_table_alias = null;
  
  // Base table is taxonomy_term_data
  if($view->base_table == 'taxonomy_term_data') {
      $taxonomy_term_table_alias = 'taxonomy_term_data';
      $join = views_get_table_join('taxonomy_index', 'taxonomy_term_data');
      $query->add_relationship("taxonomy_index_taxonomy_term_data", $join, 'taxonomy_index', NULL);
  }
  else {

    // If taxonomy is not at base table try to find a relation with it.
    // Actually I take in account only node

    $taxonomy_term_table_alias = (isset($query->tables['taxonomy_term_data'])) ? 'taxonomy_term_data' : null;
    $field_tid = 'tid';
    // got taxonomy_term_data ?
    if( is_null($taxonomy_term_table_alias) ) {

        // search if there is a reference, if so take the first
        foreach($query->relationships as $alias => $relationship) {
            if( $relationship['base'] == 'taxonomy_term_data' ) {
                $taxonomy_term_table_alias = $alias;
              break;
            }
        }

        if(!is_null($taxonomy_term_table_alias)) {

  //         // TEST 1: alter existing relationships (near to work..)
  //         unset( $query->table_queue[ $taxonomy_term_table_alias ] );
  //         unset( $query->relationships[ $taxonomy_term_table_alias ] );
  //         $join = views_get_table_join('taxonomy_term_data', 'taxonomy_index');
  //         $query->add_relationship($taxonomy_term_table_alias, $join, 'taxonomy_index');

            // TEST 2: add new relationships, seems OK

            if(!isset($query->table_queue['taxonomy_index'])) {
              $query->ensure_table('taxonomy_index');
            }

            // tagadelic_taxonomy_index
            $join = $query->table_queue['taxonomy_index']['join'];
            $query->add_relationship('tagadelic_taxonomy_index', $join, 'taxonomy_index', 'node');
            // tagadelic_taxonomy_term_data
            $join = views_get_table_join('taxonomy_term_data', 'taxonomy_index');
            $query->add_relationship('tagadelic_taxonomy_term_data', $join, 'tagadelic_taxonomy_index');

            // Add some term information needed by tagadelic (tid, vid)
            $field_tid = $query->add_field($taxonomy_term_table_alias, 'tid', 'taxonomy_term_data_tag_tid');
            $query->add_field($taxonomy_term_table_alias, 'vid', 'taxonomy_term_data_tag_vid');
        }
        else {
            views_debug(t("Consider adding at least a relationship to a taxonomy term to get (better) results."));
        }

    }

  }
  
  $field_name_count     = $query->add_field($taxonomy_term_table_alias, 'name', $alias = 'taxonomy_term_data_tag_count', $params = array('function' => 'count'));
  $field_name           = $query->add_field($taxonomy_term_table_alias, 'name', $alias = 'taxonomy_term_data_tag_name');
  $field_desc           = $query->add_field($taxonomy_term_table_alias, 'description', $alias = 'taxonomy_term_data_tag_description');

  $query->distinct = TRUE;
  $query->no_distinct = $field_tid;
//  $query->set_distinct(TRUE, TRUE);
  $query->add_groupby($field_tid);

  $query->add_having_expression( 0, 'taxonomy_term_data_tag_count > 0' );

//  dsm($view);
//  dsm($query);
}

/**
 *
 * Implementation of hook_views_pre_execute
 *
 */
//function tagadelic_views_views_pre_execute(&$view) {}

/**
 *
 * Implementation of hook_views_post_build
 *
 */
//function tagadelic_views_views_post_build(&$view) {}
