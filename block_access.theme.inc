<?php

/**
 * @file
 * Themes for block_access module.
 */

/**
 * Theme function for the admin list form.
 */
function theme_block_access_admin_list($form) {

  $header = array(
    t('Module'),
    t('Current Settings'),
    t('Operations'),
  );

  $rows = array();
  foreach ($form['list'] as $key => $element) {
    if (is_numeric($key)) {
      $row = array();
      $module = $element['name']['#value'];
      $row[] = $module;
      $roles = block_access_get_module($module);
      if (empty($roles)) {
        $row[] = 'None';
      }
      else {
        $names = user_roles();
        $output = '<ul>';
        foreach($roles as $rid => $perms) {
          $role = $names[$rid];
          $output .= '<li>'.$role.'<ul>';
          foreach ($perms as $perm) {
            $output .= '<li>'.$perm.'</li>';
          }
          $output .= '</ul></li>';
        }
        $output .= '</ul>';
        $row[] = $output;
      }
      $row[] = l(t('edit'), BLOCK_ACCESS_SETTINGS . '/edit/'. $module);
      $rows[] = array('data' => $row);
      unset($form['list'][$key]);
    }
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No modules found.'), 'colspan' => 2));
    array_pop($header);
  }

  $form['list']['table'] = array('#value' => theme('table', $header, $rows, array('id' => 'block_access-list-table')));
  return 'This is a list of modules which expose blocks. Here you can define default permissions on a per module basis to be used when new blocks get created.'.drupal_render($form);
}

