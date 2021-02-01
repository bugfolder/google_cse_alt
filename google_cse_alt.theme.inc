<?php

/**
 * @file
 * Themeable functions for Google Custom Search Engine.
 */


/**
 * Return the CSE tag for the desired display mode.
 */
function google_cse_alt_get_cse_tag($id) {
  $config_name = _google_cse_alt_config_name();
  $display = config_get($config_name, "google_cse_alt_custom_results_display_{$id}");
  $attributes = filter_xss(config_get($config_name, "google_cse_alt_tag_attributes_{$id}"));

  switch ($display) {
    case 'overlay':
    case 'compact':
    case 'full-width':
      return '<gcse:search ' . $attributes . '></gcse:search>';

    case 'two-page':
      return '<gcse:searchbox-only ' . $attributes . '></gcse:searchbox-only><gcse:searchresults-only ' . $attributes . '></gcse:searchresults-only>';

    case 'two-column':
      return '<gcse:searchbox ' . $attributes . '></gcse:searchbox><gcse:searchresults ' . $attributes . '></gcse:searchresults>';

    case 'results-only':
      return '<gcse:searchresults-only ' . $attributes . '></gcse:searchresults-only>';

    case 'google-hosted':
      return '<gcse:searchbox-only ' . $attributes . '></gcse:searchbox-only>';

    default:
      watchdog('google_cse_alt', 'Invalid custom result display %display',
               array('%display' => $display), WATCHDOG_CRITICAL);
  }
}


/**
 * Theme/customize the search results page.
 */
function template_preprocess_google_cse_alt_results(&$variables) {
  $config_name = _google_cse_alt_config_name();
  $id = $variables['cse_id'];

  $results_searchbox_form = $variables['form'] ?
    backdrop_get_form('google_cse_alt_results_searchbox_form', $id) : '';

// $fooform = $results_searchbox_form;
// dpm($fooform,'$fooform');
// this would be a place to append $id to to $results_searchbox_form['#form_id'] to give it a unique ID, but we still need to get the id into the Javascript processor in google_cse_alt_results.js.

  $variables['results_searchbox_form'] = $results_searchbox_form;

  $variables['cse_tag'] = google_cse_alt_get_cse_tag($id);
  $variables['noscript'] = t('You must enable JavaScript to view the search results.');
  $variables['prefix'] =
    filter_xss_admin(config_get($config_name, "google_cse_alt_results_prefix_{$id}"));
  $variables['suffix'] =
    filter_xss_admin(config_get($config_name, "google_cse_alt_results_suffix_{$id}"));

  if (google_cse_alt_validate_request($id)) {
    backdrop_add_js(
      backdrop_get_path('module', 'google_cse_alt') . '/js/google_cse_alt_results.js',
        array('scope' => 'footer'));
    backdrop_add_css(config_get($config_name, "google_cse_alt_custom_css_{$id}"),
      'external');
  }
}


/**
 * Validate GET parameters to avoid displaying inappropriate search results.
 */
function google_cse_alt_validate_request($id) {
  $config_name = _google_cse_alt_config_name();
  return (empty($_GET['cx']) ||
    $_GET['cx'] ==config_get($config_name, "google_cse_alt_cx_{$id}"));
}


/**
 * Form builder for the searchbox forms.
 */
function google_cse_alt_results_searchbox_form($form, &$form_state, $id = '') {
  $config_name = _google_cse_alt_config_name();
  $form = array();
  $form['#attributes'] = array('class' => "google-cse-alt-id-{$id}");

  if (config_get($config_name, "google_cse_alt_results_display_{$id}") == 'here') {
    $cof = config_get($config_name, "google_cse_alt_cof_here_{$id}");
  }
  else {
    $form['#action'] = '//' .
      config_get($config_name, 'google_cse_alt_domain') . '/cse';
    $cof = config_get($config_name, "google_cse_alt_cof_google_{$id}");
  }
  $form['#method'] = 'get';

  $form['cx'] = array(
    '#type' => 'hidden',
    '#value' => config_get($config_name, "google_cse_alt_cx_{$id}"),
  );

  $form['cof'] = array(
    '#type' => 'hidden',
    '#value' => $cof,
  );

  $form['query'] = array(
    '#type' => 'textfield',
    '#title' => config_get($config_name, "google_cse_alt_results_searchbox_title_{$id}"),
    '#size' => config_get($config_name, "google_cse_alt_results_searchbox_width_{$id}"),
    '#default_value' => isset($_GET['query']) ? $_GET['query'] : '',
  );
  $placeholder = config_get($config_name, "google_cse_alt_placeholder_{$id}");
  if (!empty($placeholder)) {
    $form['query']['#attributes'] = array('placeholder' => $placeholder);
  }

  $glyph = config_get($config_name, "google_cse_alt_glyph_{$id}");
  if (empty($glyph)) {
    $form['sa'] = array(
      '#type' => 'submit',
      '#value' => "Search",
    );
  }
  else {
    $form['sa'] = array(
      '#type' => 'submit',
      '#value' => " ",
    );
    $form['glyph'] = array(
      '#markup' => strip_tags($glyph, '<i><span>'),
      '#prefix' => '<span class="google-cse-alt-search-glyph">',
      '#suffix' => '</span>',
    );
  }
  return $form;
}
