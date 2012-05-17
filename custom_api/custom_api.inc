<?php
/**
 * Callback for retrieving custom resource.
 *
 * @param int $id
 *
 * @return object
 */
function _custom_api_retrieve_resource($id) {
  // Compute a simple arithmetic function.
  $value = $id + 1;

  $response = array(
    'custom' => $value,
    'message' => 'Incrementing is easy.',
  );

  return $response;
}

/**
 * Access callback for the resources.
 *
 * @param string $op
 *   The requested operation to grant access to, or not.
 * @param array $args
 *   The arguments that will be passed to the callback, if access is granted.
 *
 * @return bool
 *   Whether access is granted or not.
 */
function _custom_api_access($op, $args) {
/*
  // only evaluate and grant access under SSL protection
  global $is_https;
  if (!$is_https) {
    return FALSE;
  }
*/

  $access = FALSE;

  switch ($op) {
  case 'view':
    // Only the special API provider account should have the necessary role (api provider).
    // And only that role should have this particular permission enabled.
    $access = user_access('retrieve custom api resource');

    if ($access) {
      // Add other access conditions here, if any.

      // Example:
      // $id = $args[0];
      // $item = _custom_api_get_item($id);
      // $access = isset($item);
    }
    break;
  }

  return $access;
}
?>
