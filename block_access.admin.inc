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

function block_access_module_form(&$form_state, $op = NULL, $module = NULL) {
  $form = array();
  $form['module'] = array(
    '#type' => 'hidden',
    '#value' => $module
  );
  $roles = user_roles();
  block_access_fieldset($form, $roles, 'view', $module);
  block_access_fieldset($form, $roles, 'move', $module);
  block_access_fieldset($form, $roles, 'enable', $module);
  block_access_fieldset($form, $roles, 'disable', $module);
  block_access_fieldset($form, $roles, 'config', $module);
  block_access_fieldset($form, $roles, 'delete', $module);
  block_access_fieldset($form, $roles, 'config_lang', $module);
  block_access_fieldset($form, $roles, 'config_spec', $module);
  block_access_fieldset($form, $roles, 'config_user', $module);
  block_access_fieldset($form, $roles, 'config_role', $module);
  block_access_fieldset($form, $roles, 'config_page', $module);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function block_access_module_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $module = $values['module'];
  block_access_config_set_roles('view',        $values['view_roles'], $module);
  block_access_config_set_roles('move',        $values['move_roles'], $module);
  block_access_config_set_roles('enable',      $values['enable_roles'], $module);
  block_access_config_set_roles('disable',     $values['disable_roles'], $module);
  block_access_config_set_roles('config',      $values['config_roles'], $module);
  block_access_config_set_roles('delete',      $values['delete_roles'], $module);
  block_access_config_set_roles('config_lang', $values['config_lang_roles'], $module);
  block_access_config_set_roles('config_spec', $values['config_spec_roles'], $module);
  block_access_config_set_roles('config_user', $values['config_user_roles'], $module);
  block_access_config_set_roles('config_role', $values['config_role_roles'], $module);
  block_access_config_set_roles('config_page', $values['config_page_roles'], $module);
}
