<?php
/**
 * The settings form.
 */
function debug_search_solr_settings_form($form, &$form_state) {
  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-upgrade',
  );
  $form['tabs']['debug'] = debug_search_solr_solr_debug();

  $form['#submit'][] = 'debug_search_solr_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Returns form content for general settings tab.
 *
 * @return array
 *   Form item.
 */
function debug_search_solr_solr_debug() {

  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Debug Solr'),
    '#description' => t(''),
    '#weight' => 0,
  );

  $form['debug_search_solr_settings_debug_output'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug output from Solr Queries'),
    '#default_value' => variable_get('debug_search_solr_settings_debug_output', FALSE),
    '#description' => t('If checked, then Solr Queries debug output will be rendered using devel module. This should be disabled in production environments!'),
  );

  $form['debug_search_solr_settings_devel_control'] = array(
    '#type' => 'checkbox',
    '#title' => t('Control disabling Devel module.'),
    '#default_value' => variable_get('debug_search_solr_settings_devel_control', FALSE),
    '#description' => t('If left unchecked Devel will remain enabled even if debugging is disabled above. If checked devel will be disabled if the above is unchecked.'),
  );

  return $form;
}

/**
 * Submit handler for the settings form.
 *
 */
function debug_search_solr_settings_form_submit($form, &$form_state) {
  if($form_state['values']['debug_search_solr_settings_debug_output'] == 1) {
    // enable devel module
    if (!module_exists('devel')) {
      module_enable(array('devel'));
      drupal_set_message(t('Devel was enabled!'));
    }
    drupal_set_message(t('Solr debugging has been enabled!'));
  }
  else {
    if($form_state['values']['debug_search_solr_settings_devel_control'] == 1) {
      if (module_exists('devel')) {
        module_disable(array('devel'));
        drupal_set_message(t('Devel was disabled!'));
      }
    }
    drupal_set_message(t('Solr debugging has been disabled!'));
  }
}
