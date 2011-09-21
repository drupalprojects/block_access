<?php
// $Id$
/* 
 * @file block_access.db.inc
 * DB interface for block_access module
 */

/*
 * delete a block_access permission for a module or specific block for all roles
 * @param $module - the name of the module
 * @param $module - the permission being removed
 * @param $delta  - optional block delta
 */
function block_access_delete_roles($module, $perm, $delta=NULL) {
  $delete = db_delete('block_access_roles')
    ->condition('module', $module, '=')
    ->condition('permission', $perm, '=');
  if ($delta !== NULL) {
    $delete->condition('delta', $delta, '=');
  }
  else {
    $delete->isNull('delta');
  }
  $delete->execute();
}

/*
 * insert a block_access_roles record
 * @param $rid - role ID
 * @param $module - the name of the module
 * @param $perm - the permission being added
 * @param $delta - optional block delta
 */
function block_access_add_role($rid, $module, $perm, $delta=NULL) {
  $record = array($rid, $module, $delta, $perm);
  drupal_write_record('block_access_roles', $record);
}

/*
 * fetch roles defined for a given module/perm/block
 * @param $module - the name of the module
 * @param $perm - the permission
 * @param $delta - optional block delta
 * @returns array of role IDs
 */
function block_access_get_roles($module, $perm, $delta=NULL) {
  $query = db_select('block_access_roles', 'b')
    ->fields('b', array('rid'))
    ->condition('module', $module, '=')
    ->condition('permission', $perm, '=')
    ->condition('delta', $delta, '=');

  $result = $query->execute();

  // If we didn't find any for the delta, use the module defaults
  if ($delta && empty($result)) {
    $query->isNull('delta');
    $result = $query->execute();
  }

  $ret = array();
  foreach ($result as $record) {
    $ret[] = $record['rid'];
  }

  return $ret;
}

/*
 * get permissions for a given module
 * @param $module - the name of the module
 * @returns an array of Role IDs and their permissions
 */
function block_access_get_module($module) {
  $query = db_select('block_access_roles', 'b')
    ->fields('b', array('rid', 'permission'))
    ->condition('module', $module, '=')
    ->isNull('delta');

  $result = $query->execute();
  $ret = array();
  while ($ob = $result->fetchObject()) {
    if (isset($ret[$ob->rid])) {
      $ret[$ob->rid][] = $ob->permission;
    }
    else {
      $ret[$ob->rid] = array($ob->permission);
    }
  }
  return $ret;
}

