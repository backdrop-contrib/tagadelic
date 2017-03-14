<?php
/**
 * @file
 * Administration settings page and associated functions.
 */

/**
 * Menu callback. Admin setting page for tagadelic.
 */
function tagadelic_settings() {
  $config = config('tagadelic.settings');

  $form['tagadelic_page_amount'] = array(
    '#type' => 'number',
    '#title' => t('Number of tags to show on Tagadelic pages'),
    '#default_value' => $config->get('page_amount'),
    '#description' => t('The number of tags that will show up in a cloud. Number of tags tp show in each block must be configured in block settings.'),
  );
  $form['tagadelic_levels'] = array(
    '#type' => 'number',
    '#title' => t('Number of levels'),
    '#default_value' => $config->get('levels'),
    '#description' => t('The number of levels between the least popular tags and the most popular ones. Each levels will be shown as a different size.'),
  );
  $options = array('weight,asc' => t('by weight, ascending'), 'weight,desc' => t('by weight, descending'), 'title,asc' => t('by title, ascending'), 'title,desc' => t('by title, descending'), 'random,none' => t('random'));
  $form['tagadelic_sort_order'] = array(
    '#type' => 'radios',
    '#title' => t('Tagadelic sort order'),
    '#options' => $options,
    '#default_value' => $config->get('sort_order'),
  );

  // Add a submit button.
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for module_settings_form().
 */
function tagadelic_settings_submit($form, &$form_state) {
  $config = config('tagadelic.settings');
  $config->set('sort_order', $form_state['values']['tagadelic_sort_order']);
  $config->set('page_amount', $form_state['values']['tagadelic_page_amount']);
  $config->set('levels', $form_state['values']['tagadelic_levels']);
  $config->save();
  backdrop_set_message(t('The Tagadelic configuration options have been saved.'));
}
