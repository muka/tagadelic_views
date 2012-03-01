<?php
/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class tagadelic_plugin_style extends views_plugin_style_list {
  /**
   * Set default options
   */
  function option_definition() {
//    $options = parent::option_definition();
    $options = array();
    $options['steps'] = 6;

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
//    parent::options_form($form, $form_state);
//    $steps = 6;
//    $size = 60;
    $form['steps'] = array(
      '#type' => 'textfield',
      '#title' => t('Steps'),
      '#default_value' => $this->options['steps'] ? $this->options['steps'] : 6,
    );
   
  }
  
  function render(){
    /* 
     * function tagadelic_build_weighted_tags($tags, $steps = 6) {
     * 
     *    $tag: $tag->count, $tag->tid, $tag->name $tag->vid.
    */
    $steps = 6;
    if(isset($this->view->style_plugin->options['steps'])){
      $steps = $this->view->style_plugin->options['steps'];
    }
//    dsm($steps);
    
    $size = count($this->view->result);
    // count, td.tid, td.vid, td.name, td.description 
    $tags = array();
    
    foreach ($this->view->result as $term){
      $tags[ $term->tid ] = new StdClass(); 
      $tags[ $term->tid ]->name = $term->taxonomy_term_data_name;
      $tags[ $term->tid ]->tid = $term->tid;
      $tags[ $term->tid ]->vid = $term->taxonomy_term_data_vid;
      $tags[ $term->tid ]->count = $term->taxonomy_term_data_tag_count;
      $tags[ $term->tid ]->description = $term->taxonomy_term_data_description;
    }
    
    $tags = tagadelic_build_weighted_tags($tags);    
    /// @todo: use views sorting options
    $tags = tagadelic_sort_tags($tags);

    $output = theme('tagadelic_weighted', array('terms' => $tags));        

   
    return $output;    
    
  }
  
}

//
///**
// * @file
// * Handler for tagadelic_plugin_style.
// */
//class tagadelic_plugin_style extends views_plugin_style_list {
//
//  function render() {
////    $options = $this->display->handler->get_option('tagadelic_options');
//    
////    dsm($this->view->query);
////
////    $fieldsMap = array();
////    foreach ($this->view->field as $field_name => $viewFieldObj){
////      foreach ($this->view->query->fields as $queryFieldName => $queryFieldData){
////        if($queryFieldData['field'] == $field_name){
////          $fieldsMap[ $field_name ] = $queryFieldName;
////        }
////      }
////    }
//    
////    dsm($this->view->result);
////    dsm($fieldsMap);
////    
////    $steps = 6;
////    $size = 60;
////    // count, td.tid, td.vid, td.name, td.description 
////    $tags = array();
////    
////    foreach ($this->view->result as $term){
////      krumo($term, $fieldsMap);die();
////      if(isset($tags[ $term->tid ])){
////        $tags[ $term->tid ]->count++;
////        continue;
////      }
////      
////      $tags[ $term->tid ] = new StdClass(); 
////      $tags[ $term->tid ]->name = $term->{$fieldsMap['name']};
////      $tags[ $term->tid ]->tid = $term->tid;
////      $tags[ $term->tid ]->vid = $term->{$fieldsMap['vid']};
////      $tags[ $term->tid ]->count = 1;
////      $tags[ $term->tid ]->description = isset($term->{$fieldsMap['description']}) ? $term->{$fieldsMap['description']} : "";
////    }
////    
////    $tags = tagadelic_build_weighted_tags($tags);
////    $tags = tagadelic_sort_tags($tags);
////    
////    dsm($tags);
//    return $results;
//  }
//}
