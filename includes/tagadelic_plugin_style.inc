<?php

/**
 * @file
 * Contains the tagadelic style plugin.
 */

/**
 * Style plugin to render a weighted set of taxonomy terms.
 *
 * @ingroup tagadelic_style_plugins
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

  function render() {
    /*
     * function tagadelic_build_weighted_tags($tags, $steps = 6) {
     *
     *    $tag: $tag->count, $tag->tid, $tag->name $tag->vid.
     */
    $steps = 6;
    if (isset($this->view->style_plugin->options['steps'])) {
      $steps = $this->view->style_plugin->options['steps'];
    }

    $size = count($this->view->result);

    // count, td.tid, td.vid, td.name, td.description
    // Create a term-like object for `tagadelic_build_weighted_tags()`

    $tags = array();
    foreach ($this->view->result as $term) {

//      dsm($term);

      $tid = isset($term->taxonomy_term_data_tag_tid) ? $term->taxonomy_term_data_tag_tid : $term->tid;
      $vid = isset($term->taxonomy_term_data_vid) ? $term->taxonomy_term_data_vid: $term->taxonomy_term_data_tag_vid;

      $tags[$tid] = new StdClass();
      $tags[$tid]->name = $term->taxonomy_term_data_tag_name;
      $tags[$tid]->tid = $tid;
      $tags[$tid]->vid = $vid;
      $tags[$tid]->count = $term->taxonomy_term_data_tag_count;
      $tags[$tid]->description = $term->taxonomy_term_data_tag_description;
    }

    $tags = tagadelic_build_weighted_tags($tags);
    /// @todo: use views sorting options
//    $tags = tagadelic_sort_tags($tags);

    /// @TODO: check tagadelic requirement for vocabulary reference or rewrite theme function
    $voc = new StdClass();
    $voc->vid = 0;

    $output = theme('tagadelic_weighted', array('terms' => $tags, 'voc' => $voc, 'more_link' => FALSE));


    return $output;
  }

}

