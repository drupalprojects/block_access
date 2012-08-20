<?php
// $Id$
/*
 * @file block_access.admin.inc
 * Admin interfaces for block_access module
 */

function block_access_admin_list() {
  $form['list'] = array();
  $modules = module_implements('block_info');
  return theme('block_access_admin_list', array('modules' => $modules));
}

function block_access_module_form($form, &$form_state, $module) {
  $delta = 0;
  $current_theme = variable_get('theme_default','none');
  
  $form = array();
  $form['module'] = array(
    '#type' => 'hidden',
    '#value' => $module
  );
  $form['delta'] = array(
    '#type' => 'hidden',
    '#value' => $delta, 
  );
  
  $role_options = user_roles();
  // Add fieldset for each permission
  $form['role_basic_ops_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => false,
  );
  
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'view', $module, $delta, 'can view block');
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'move', $module, $delta, 'can move block');
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'enable', $module, $delta, 'can enable block');
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'disable', $module, $delta, 'can disable block');
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'delete', $module, $delta,'can delete block');
  block_access_fieldset($form['role_basic_ops_fieldset'], $role_options, 'config', $module, $delta, 'can configure block');
  
  $form['role_config_ops_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration Specific Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => false,
  );
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_lang', $module, $delta, 'can change title language');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_title', $module, $delta, 'can change block title');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_desc', $module, $delta, 'can change block description');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_body', $module, $delta, 'can change block body');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_region', $module, $delta, 'can change block region');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_page_visibility', $module, $delta, 'can change block page visibility');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_type_visibility', $module, $delta, 'can change block type visibility');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_role_visibility', $module, $delta, 'can change block role visibility');
  block_access_fieldset($form['role_config_ops_fieldset'], $role_options, 'config_user_visibility', $module, $delta, 'can change block user visibility');
  
  // Grab the list of available regions
/*  $theme_list = list_themes();
  $region_list = array();
  foreach ($theme_list as $theme) {
    if ($theme->status == 1) { // Only enabled themes
      $tmp_region_list = system_region_list($theme->name);
      $region_list = array_merge($region_list, $tmp_region_list);
    }
  }
 */
  $region_list = system_region_list($current_theme);
  
  //$region_list = array_unique($region_list); // No duplicates
  $form['role_region_specific_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Region specific settings'),
    '#collapsible' => TRUE,
    '#collapsed' => false,
  );
  
  foreach ($region_list as $region_name => $realname) {
    block_access_fieldset($form['role_region_specific_fieldset'], $role_options, "dreg_$region_name", $module, $delta, "cannot access region `$region_name`");
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function block_access_module_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $module = $values['module'];
  $delta = $values['delta'];
  $current_theme = variable_get('theme_default','none');
  
  block_access_config_set_roles('view',          $values['view_roles'], $module, $delta);
  block_access_config_set_roles('move',          $values['move_roles'], $module, $delta);
  block_access_config_set_roles('enable',        $values['enable_roles'], $module, $delta);
  block_access_config_set_roles('disable',       $values['disable_roles'], $module, $delta);
  block_access_config_set_roles('config',        $values['config_roles'], $module, $delta);
  block_access_config_set_roles('delete',        $values['delete_roles'], $module, $delta);
  block_access_config_set_roles('config_lang',   $values['config_lang_roles'], $module, $delta);
  block_access_config_set_roles('config_title',  $values['config_title_roles'], $module, $delta);
  block_access_config_set_roles('config_desc',   $values['config_desc_roles'], $module, $delta);
  block_access_config_set_roles('config_body',   $values['config_body_roles'], $module, $delta);
  block_access_config_set_roles('config_region', $values['config_region_roles'], $module, $delta);
  block_access_config_set_roles('config_type',   $values['config_type_visibility_roles'], $module, $delta);
  block_access_config_set_roles('config_user',   $values['config_user_visibility_roles'], $module, $delta);
  block_access_config_set_roles('config_role',   $values['config_role_visibility_roles'], $module, $delta);
  block_access_config_set_roles('config_page',   $values['config_page_visibility_roles'], $module, $delta);
  
  $region_list = system_region_list($current_theme);
  
  //$region_list = array_unique($region_list); // No duplicates
  
  foreach ($region_list as $region_name => $realname) {
    if (isset($values["dreg_{$region_name}_roles"])) {
      block_access_config_set_roles("dreg_{$region_name}",   $values["dreg_{$region_name}_roles"], $module, $delta);
    }
    
  }

  drupal_set_message("Settings have been updated");
}
