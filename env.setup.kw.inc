<?php

/**
 * @file
 * This file contains the functions that are required to execute
 * `drush kw-setup-env`.
 */

/**
 * Implements drush_COMMAND_init() for `drush kw-setup-env`.
 */
function drush_kw_setup_env_init() {
  kraftwagen_context_init_kraftwagen_root();
}

/**
 * Implements drush_COMMAND for `drush kw-setup-env`.
 */
function drush_kraftwagen_kw_setup_env() {
  // Find out where the Kraftwagen root is.
  $root = kraftwagen_context_get_option('root-path');

  // Determine config directory.
  if (!($dir_cnf = kraftwagen_context_get_option('cnf-dir'))) {
    return drush_set_error(dt('No cnf dir name set.'));
  }

  if (!is_dir($root . DIRECTORY_SEPARATOR . $dir_cnf)) {
    drush_mkdir($root . DIRECTORY_SEPARATOR . $dir_cnf);
    drush_log(dt('Config directory !dir created', array('!dir' => $root . DIRECTORY_SEPARATOR . $dir_cnf)), 'success');
  }
  else {
    drush_log(dt('Config directory !dir already exists', array('!dir' => $root . DIRECTORY_SEPARATOR . $dir_cnf)), 'warning');
  }

  // determine builds directory
  if (!($dir_builds = kraftwagen_context_get_option('builds-dir'))) {
    return drush_set_error(dt('No builds dir name set.'));
  }

  if (!is_dir($root . DIRECTORY_SEPARATOR . $dir_builds)) {
    drush_mkdir($root . DIRECTORY_SEPARATOR . $dir_builds);
    drush_log(dt('Config directory !dir created', array('!dir' => $root . DIRECTORY_SEPARATOR . $dir_builds)), 'success');
  } else {
    drush_log(dt('Config directory !dir already exists', array('!dir' => $root . DIRECTORY_SEPARATOR . $dir_builds)), 'warning');
  }

  if (!($file_environment = kraftwagen_context_get_option('environment-file'))) {
    return drush_set_error(dt('No environment file set.'));
  }

  if (!file_exists($root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment)) {
    if (!($default_environment = kraftwagen_context_get_option('environment-default'))) {
      return drush_set_error(dt('No default environment set.'));
    }

    file_put_contents($root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment, $default_environment);

    drush_log(dt('Setup environment in !file to !environment', array('!file' => $root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment, '!environment' => $default_environment)), 'success');

    drush_log(dt('If you are on a development machine, you\'ll want to change !path to \'development\'.', array('!path' => $root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment, '!environment' => $default_environment)), 'ok');
  }
  else {
    drush_log(dt('Environment already set in !file', array('!file' => $root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment)), 'warning');
  }
}
