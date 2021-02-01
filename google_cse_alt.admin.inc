<?php
/**
 * @file
 * Admin settings for Google Custom Search Engine.
 */


/**
 * Admin settings for the CSE, either as standalone page or as subpage of Search
 * settings (called via hook_search_admin()).
 */
function google_cse_alt_admin_settings() {
  $form = array();
  $config_name = _google_cse_alt_config_name();

  $form['google_cse_alt_domain'] = array(
    '#title' => t('Google search domain'),
    '#type' => 'textfield',
    '#description' => t('Enter the Google search domain.'),
    '#default_value' => config_get($config_name, 'google_cse_alt_domain'),
  );

  $form['google_cse_alt_num_blocks'] = array(
    '#title' => t('Number of blocks'),
    '#type' => 'textfield',
    '#description' => t('Enter the number of Google Custom Search Engine blocks to create.'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => config_get($config_name, 'google_cse_alt_num_blocks'),
  );

  $num_blocks = config_get($config_name, 'google_cse_alt_num_blocks');
  for ($id = 1; $id <= $num_blocks; $id++) {
    $form["cse_block_{$id}"] = array(
      '#title' => _google_cse_alt_block_title($id),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form["cse_block_{$id}"]["google_cse_alt_name_{$id}"] = array(
      '#title' => t('Google Custom Search Engine Name'),
      '#type' => 'textfield',
      '#description' => t('Enter your <a target="_blank" href="http://www.google.com/cse/manage/all">Google CSE Name</a> (click on control panel).'),
      '#default_value' => config_get($config_name, "google_cse_alt_name_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_cx_{$id}"] = array(
      '#title' => t('Google Custom Search Engine ID'),
      '#type' => 'textfield',
      '#description' => t('Enter your <a target="_blank" href="http://www.google.com/cse/manage/all">Google CSE unique ID</a> (click on control panel).'),
      '#default_value' => config_get($config_name, "google_cse_alt_cx_{$id}"),
    );

    // Search box

    $form["cse_block_{$id}"]["search_box_{$id}"] = array(
      '#type' => 'fieldset',
      '#title' => t('Search box'),
    );

    $form["cse_block_{$id}"]["search_box_{$id}"]["google_cse_alt_show_watermark_{$id}"] = array(
      '#title' => t('Show watermark in search field'),
      '#type' => 'checkbox',
      '#description' => t('If set, the Google Custom Search watermark will be in the search box.'),
      '#default_value' => config_get($config_name, "google_cse_alt_show_watermark_{$id}"),
    );

    $form["cse_block_{$id}"]["search_box_{$id}"]["google_cse_alt_placeholder_{$id}"] = array(
      '#title' => t('Placeholder text'),
      '#type' => 'textfield',
      '#description' => t('Enter placeholder text to go in the search box if you are not showing the watermark (don\'t select both).'),
      '#default_value' => config_get($config_name, "google_cse_alt_placeholder_{$id}"),
    );

    $form["cse_block_{$id}"]["search_box_{$id}"]["google_cse_alt_glyph_{$id}"] = array(
      '#title' => t('Glyph HTML'),
      '#type' => 'textfield',
      '#description' => t('You can replace the "Search" button text with a glyph if you wish. For example, use \'!glyph\' for the FontAwesome search icon (make sure you have FontAwesome installed, of course). Only &lt;i&gt; and &lt;span&gt; tags are allowed.', array('!glyph' => '&lt;span class="fas fa-search"&gt;&lt;/span&gt;')),
      '#default_value' => config_get($config_name, "google_cse_alt_glyph_{$id}"),
    );

    $form["cse_block_{$id}"]["search_box_{$id}"]["google_cse_alt_results_searchbox_title_{$id}"] = array(
      '#title' => t('Google CSE block searchbox title'),
      '#type' => 'textfield',
      '#description' => t('Enter the desired title of the searchbox in the Google CSE block.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_searchbox_title_{$id}"),
    );

    $form["cse_block_{$id}"]["search_box_{$id}"]["google_cse_alt_results_searchbox_width_{$id}"] = array(
      '#title' => t('Google CSE block searchbox width'),
      '#type' => 'textfield',
      '#maxlength' => 4,
      '#size' => 6,
      '#description' => t('Enter the desired width in characters of the searchbox in the Google CSE block.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_searchbox_width_{$id}"),
    );

    // Results

    $form["cse_block_{$id}"]["google_cse_alt_results_tab_{$id}"] = array(
      '#title' => t('Search results tab name'),
      '#type' => 'textfield',
      '#maxlength' => 50,
      '#size' => 60,
      '#description' => t('Enter a custom name of the tab where search results are displayed (defaults to %google).',
        array('%google' => t('Google'))),
      '#default_value' => config_get($config_name, "google_cse_alt_results_tab_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_results_width_{$id}"] = array(
      '#title' => t('Search results frame width'),
      '#type' => 'textfield',
      '#maxlength' => 4,
      '#size' => 6,
      '#description' => t('Enter the desired width, in pixels, of the search frame.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_width_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_cof_here_{$id}"] = array(
      '#title' => t('Ad format on this site'),
      '#type' => 'radios',
      '#options' => array(
        'FORID:9' => t('Right'),
        'FORID:10' => t('Top and right'),
        'FORID:11' => t('Top and bottom'),
      ),
      '#description' => t('Ads on the right increase the width of the iframe. Non-profit organizations can disable ads in the Google CSE control panel.'),
      '#default_value' => config_get($config_name, "google_cse_alt_cof_here_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_cof_google_{$id}"] = array(
      '#title' => t('Ad format on Google'),
      '#type' => 'radios',
      '#options' => array(
        'FORID:0' => t('Right'),
        'FORID:1' => t('Top and bottom'),
      ),
      '#description' => t('AdSense ads are also displayed when the CSE links or redirects to Google.'),
      '#default_value' => config_get($config_name, "google_cse_alt_cof_google_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_results_prefix_{$id}"] = array(
      '#title' => t('Search page prefix text'),
      '#type' => 'textarea',
      '#cols' => 50,
      '#rows' => 4,
      '#description' => t('Enter text to appear on the search page before the search form.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_prefix_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_results_suffix_{$id}"] = array(
      '#title' => t('Search page suffix text'),
      '#type' => 'textarea',
      '#cols' => 50,
      '#rows' => 4,
      '#description' => t('Enter text to appear on the search page after the search form and results.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_suffix_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_results_display_{$id}"] = array(
      '#title' => t('Display search results'),
      '#type' => 'radios',
      '#options' => array(
        'here' => t('On this site (requires JavaScript)'),
        'google' => t('On Google'),
      ),
      '#description' => t('Search results for the Google CSE block can be displayed on this site, using JavaScript, or on Google, which does not require JavaScript.'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_display_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_results_display_images_{$id}"] = array(
      '#title' => t('Display thumbnail images in the search results'),
      '#type' => 'checkbox',
      '#description' => t('If set, search result snippets will contain a thumbnail image'),
      '#default_value' => config_get($config_name, "google_cse_alt_results_display_images_{$id}"),
    );

    $form["cse_block_{$id}"]["google_cse_alt_tag_attributes_{$id}"] = array(
      '#title' => t('Google CSE Tag Attributes'),
      '#type' => 'textfield',
      '#description' => t('Enter any additional tag attributes you want in the GCSE tag. Defaults to gname="google_cse_alt". A list of attributes can be found here: <a href="https://developers.google.com/custom-search/docs/element#supported_attributes">Google Custom Search supported attributes</a>'),
      '#default_value' => config_get($config_name, "google_cse_alt_tag_attributes_{$id}"),
    );

    $form["cse_block_{$id}"]['advanced']["google_cse_alt_custom_css_{$id}"] = array(
      '#title' => t('Stylesheet Override'),
      '#type' => 'textfield',
      '#description' => t('Set a custom stylesheet to override or add any styles not allowed in the CSE settings (such as "background-color: none;"). Include <span style="color:red; font-weight:bold;">!important</span> for overrides.<br/>Example: <em>//replacewithrealsite.com/sites/all/modules/google_cse_alt/default.css</em>'),
      '#default_value' => config_get($config_name, "google_cse_alt_custom_css_{$id}"),
    );

    $form["cse_block_{$id}"]['advanced']["google_cse_alt_custom_results_display_{$id}"] = array(
      '#title' => t('Layout of Search Engine'),
      '#type' => 'radios',
      '#options' => array(
        'overlay' => t('Overlay'),
        'two-page' => t('Two page'),
        'full-width' => t('Full width'),
        'two-column' => t('Two column'),
        'compact' => t('Compact'),
        'results-only' => t('Results only'),
        'google-hosted' => t('Google hosted'),
      ),
      '#description' => t('Set the search engine layout, as found in the Layout tab of <a target="_blank" href="@url">Custom Search settings</a>.', array(
          '@url' => 'https://www.google.com/cse/lookandfeel/layout?cx=' .
            config_get($config_name, 'google_cse_alt_cx'),
          )),
      '#default_value' => config_get($config_name, "google_cse_alt_custom_results_display_{$id}"),
    );
  }

  if (!module_exists('search')) {
    // If no search module enabled, then this form will load at a separate route
    // under admin/config/search/cse-settings and has its own config file.
    $form['#config'] = $config_name;
    $form['#validate'][] = 'google_cse_alt_admin_settings_validate';
    $form['#submit'][] = 'google_cse_alt_admin_settings_submit';
    return system_settings_form($form);
  }
  else {
    // If the search module is enabled, then this form will load at
    // admin/config/search/settings in a fieldset as part of
    // search_admin_settings().
    $form_fieldset = array();
    $form_fieldset['google_cse_alt'] = array(
      '#title' => t('Google CSE'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    foreach ($form as $key => $value) {
      $form_fieldset['google_cse_alt'][$key] = $value;
    }
    return $form_fieldset;
  }
}


// TBD: add form validation to ensure that watermark and placeholder text aren't both set.


/**
 * Implements hook_form_FORM_ID_alter() for search_admin_settings.
 */
function google_cse_alt_form_search_admin_settings_alter(&$form, &$form_state, $form_id) {
  // If we're part of the search settings form, add additional processing to
  // add/remove config defaults if we've changed the number of blocks.
  $form['#validate'][] = 'google_cse_alt_admin_settings_validate';
  $form['#submit'][] = 'google_cse_alt_admin_settings_submit';
}


/**
 * Extra validation for admin settings form (either standalone or as part of
 * search settings).
 */
function google_cse_alt_admin_settings_validate($form, &$form_state) {
  $num_blocks = $form_state['values']['google_cse_alt_num_blocks'];
  for ($id = 1; $id <= $num_blocks; $id++) {
    $show_watermark = $form_state['values']["google_cse_alt_show_watermark_{$id}"];
    $placeholder = $form_state['values']["google_cse_alt_placeholder_{$id}"];
    if ($show_watermark && !empty($placeholder)) {
      form_set_error("google_cse_alt_placeholder_{$id}", t('You cannot show the watermark and have placeholder text.'));
    }
  }
}


/**
 * Extra submission processing for admin settings form (either standalone or as
 * part of search settings).
 */
function google_cse_alt_admin_settings_submit($form, &$form_state) {
  $config_name = _google_cse_alt_config_name();
  $config = config($config_name);
  $num_blocks_old = $form['google_cse_alt']['google_cse_alt_num_blocks']['#default_value'];
  $num_blocks = $form_state['values']['google_cse_alt_num_blocks'];

  if ($num_blocks < $num_blocks_old) {
    // We took away some blocks; remove the corresponding config variables.
    for ($id = $num_blocks + 1; $id <= $num_blocks_old; $id++) {
      $vars = array(
        'name',
        'cx',
        'show_watermark',
        'placeholder',
        'glyph',
        'results_tab',
        'results_searchbox_title',
        'results_searchbox_width',
        'results_width',
        'cof_here',
        'cof_google',
        'results_prefix',
        'results_suffix',
        'results_display',
        'results_display_images',
        'tag_attributes',
        'custom_css',
        'custom_results_display',
      );
      foreach ($vars as $var) {
        $config->clear("google_cse_alt_{$var}_{$id}");
      }
    }
  }

  if ($num_blocks > $num_blocks_old) {
    // We've increased the number of blocks. Add config variables with
    // default values.
    for ($id = $num_blocks_old + 1; $id <= $num_blocks; $id++) {
      $config->set("google_cse_alt_name_{$id}", '');
      $config->set("google_cse_alt_cx_{$id}", '');
      $config->set("google_cse_alt_show_watermark_{$id}", TRUE);
      $config->set("google_cse_alt_placeholder_{$id}", '');
      $config->set("google_cse_alt_glyph_{$id}", '');
      $config->set("google_cse_alt_results_tab_{$id}", '');
      $config->set("google_cse_alt_results_searchbox_title_{$id}", '');
      $config->set("google_cse_alt_results_searchbox_width_{$id}", 40);
      $config->set("google_cse_alt_results_width_{$id}", 600);
      $config->set("google_cse_alt_cof_here_{$id}", 'FORID:11');
      $config->set("google_cse_alt_cof_google_{$id}", 'FORID:0');
      $config->set("google_cse_alt_results_prefix_{$id}", '');
      $config->set("google_cse_alt_results_suffix_{$id}", '');
      $config->set("google_cse_alt_results_display_{$id}", 'here');
      $config->set("google_cse_alt_results_display_images_{$id}", TRUE);
      $config->set("google_cse_alt_tag_attributes_{$id}", 'gname="google_cse_alt"');
      $config->set("google_cse_alt_custom_css_{$id}", '');
      $config->set("google_cse_alt_custom_results_display_{$id}", 'results-only');
    }
  }
  $config->save();
}
