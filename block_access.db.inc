<?php
/* 
 * @file block_access.db.inc
 * DB interface for block_access module
 */

function block_access_delete_roles($module, $perm, $delta=null) {
  $sql = "
    DELETE FROM {block_access_roles} 
    WHERE module = '%s'
    AND   permission = '%s'
  ";
  $args = array($module, $perm);
  if ($delta !== null) {
    $sql .= "AND delta = '%s'";
    $args[] = $delta;
  }
  else {
    $sql .= "AND delta = ''";
  }
  db_query($sql,$args);
}

function block_access_add_role($rid, $module, $perm, $delta=null) {
  db_query("
    INSERT INTO {block_access_roles}
    (
      rid,
      module,
      delta,
      permission
    )
    VALUES
    (
      %d,
      '%s',
      '%s',
      '%s'
    )",
    $rid, $module, $delta, $perm);
}

function block_access_get_roles($module, $perm, $delta=null) {
  $ret = array();
  $sql="
    SELECT rid
    FROM {block_access_roles}
    WHERE module = '%s'
    AND   permission = '%s'
    AND   delta = '%s';
  ";

  $result = db_query($sql, $module, $perm, $delta);
  while ($rid = db_result($result)) {
    $ret[] = $rid;
  }

  // If we didn't find any for the delta, use the module defaults
  if (empty($ret)) {
    $result = db_query($sql, $module, $perm, '');
    while ($rid = db_result($result)) {
      $ret[] = $rid;
    }
  }

  return $ret;
}

function block_access_get_module($module) {
  $sql="
    SELECT rid, permission
    FROM {block_access_roles}
    WHERE module = '%s'
    AND   delta = ''";

  $result = db_query($sql, $module);
  $ret = array();
  while ($ob = db_fetch_object($result)) {
    if (isset($ret[$ob->rid])) {
      $ret[$ob->rid][] = $ob->permission;
    }
    else {
      $ret[$ob->rid] = array($ob->permission);
    }
  }
  return $ret;
}

