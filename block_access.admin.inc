<?php
/* 
 * @file block_access.admin.inc
 * Admin interfaces for block_access module
 */

function block_access_admin_list() {
  $form['list'] = array();
  $modules = module_implements('block');
  foreach($modules as $key => $module) {
    $form['list'][$key] = array(
      'name' => array('#value' => $module),
    );
  }
  return $form;
}

function block_access_module_form(&$form_state, $op = NULL, $module = NULL) {
  $form = array();
  $form['module'] = array(
    '#type' => 'hidden',
    '#value' => $module
  );
  $role_options = user_roles();
  block_access_fieldset($form, $role_options, 'view', $module);
  block_access_fieldset($form, $role_options, 'move', $module);
  block_access_fieldset($form, $role_options, 'enable', $module);
  block_access_fieldset($form, $role_options, 'disable', $module);
  block_access_fieldset($form, $role_options, 'config', $module);
  block_access_fieldset($form, $role_options, 'delete', $module);
  block_access_fieldset($form, $role_options, 'config_lang', $module);
  block_access_fieldset($form, $role_options, 'config_spec', $module);
  block_access_fieldset($form, $role_options, 'config_user', $module);
  block_access_fieldset($form, $role_options, 'config_role', $module);
  block_access_fieldset($form, $role_options, 'config_page', $module);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function block_access_module_form_submit($form, &$form_state) {
  $module = $form_state['values']['module'];
  block_access_config_set_roles('view',        $form_state['values']['view_roles'], $module);
  block_access_config_set_roles('move',        $form_state['values']['move_roles'], $module);
  block_access_config_set_roles('enable',      $form_state['values']['enable_roles'], $module);
  block_access_config_set_roles('disable',     $form_state['values']['disable_roles'], $module);
  block_access_config_set_roles('config',      $form_state['values']['config_roles'], $module);
  block_access_config_set_roles('delete',      $form_state['values']['delete_roles'], $module);
  block_access_config_set_roles('config_lang', $form_state['values']['config_lang_roles'], $module);
  block_access_config_set_roles('config_spec', $form_state['values']['config_spec_roles'], $module);
  block_access_config_set_roles('config_user', $form_state['values']['config_user_roles'], $module);
  block_access_config_set_roles('config_role', $form_state['values']['config_role_roles'], $module);
  block_access_config_set_roles('config_page', $form_state['values']['config_page_roles'], $module);
}
