<?php

/**
 * @file
 * Taxonomy Auto Tagging module English Text Processor.
 */

class TaxonomyAutoTaggingTextProcessorEn {
  /**
   * Pluralizes English nouns.
   */
  public static function pluralize($word) {
    $plural = array(
      '/(quiz)$/i' => '1zes',
      '/^(ox)$/i' => '1en',
      '/([m|l])ouse$/i' => '1ice',
      '/(matr|vert|ind)ix|ex$/i' => '1ices',
      '/(x|ch|ss|sh)$/i' => '1es',
      '/([^aeiouy]|qu)ies$/i' => '1y',
      '/([^aeiouy]|qu)y$/i' => '1ies',
      '/(hive)$/i' => '1s',
      '/(?:([^f])fe|([lr])f)$/i' => '12ves',
      '/sis$/i' => 'ses',
      '/([ti])um$/i' => '1a',
      '/(buffal|tomat)o$/i' => '1oes',
      '/(bu)s$/i' => '1ses',
      '/(alias|status)/i' => '1es',
      '/(octop|vir)us$/i' => '1i',
      '/(ax|test)is$/i' => '1es',
      '/s$/i' => 's',
      '/$/' => 's',
    );

    $uncountable = array(
      'equipment',
      'information',
      'rice',
      'money',
      'species',
      'series',
      'fish',
      'sheep',
    );

    $irregular = array(
      'person' => 'people',
      'man' => 'men',
      'child' => 'children',
      'sex' => 'sexes',
      'move' => 'moves',
    );

    $lowercased_word = strtolower($word);

    foreach ($uncountable as $_uncountable) {
      if (substr($lowercased_word, (-1 * strlen($_uncountable))) == $_uncountable) {
        return $word;
      }
    }

    foreach ($irregular as $_plural => $_singular) {
      if (preg_match('/(' . $_plural . ')$/i', $word, $arr)) {
        return preg_replace('/(' . $_plural . ')$/i', substr($arr[0], 0, 1) . substr($_singular, 1), $word);
      }
    }

    foreach ($plural as $rule => $replacement) {
      if (preg_match($rule, $word)) {
        return preg_replace($rule, $replacement, $word);
      }
    }
    return FALSE;

  }

  /**
   * Singularizes English nouns.
   */
  public static function singularize($word) {
    $singular = array(
      '/(quiz)zes$/i' => '\1',
      '/(matr)ices$/i' => '\1ix',
      '/(vert|ind)ices$/i' => '\1ex',
      '/^(ox)en/i' => '\1',
      '/(alias|status)es$/i' => '\1',
      '/([octop|vir])i$/i' => '\1us',
      '/(cris|ax|test)es$/i' => '\1is',
      '/(shoe)s$/i' => '\1',
      '/(o)es$/i' => '\1',
      '/(bus)es$/i' => '\1',
      '/([m|l])ice$/i' => '\1ouse',
      '/(x|ch|ss|sh)es$/i' => '\1',
      '/(m)ovies$/i' => '\1ovie',
      '/(s)eries$/i' => '\1eries',
      '/([^aeiouy]|qu)ies$/i' => '\1y',
      '/([lr])ves$/i' => '\1f',
      '/(tive)s$/i' => '\1',
      '/(hive)s$/i' => '\1',
      '/([^f])ves$/i' => '\1fe',
      '/(^analy)ses$/i' => '\1sis',
      '/((a)naly|(b)a|(d)iagno|(p)arenthe|(p)rogno|(s)ynop|(t)he)ses$/i' => '\1\2sis',
      '/([ti])a$/i' => '\1um',
      '/(n)ews$/i' => '\1ews',
      '/s$/i' => '',
    );

    $uncountable = array(
      'equipment',
      'information',
      'rice',
      'money',
      'species',
      'series',
      'fish',
      'sheep',
    );

    $irregular = array(
      'person' => 'people',
      'man' => 'men',
      'child' => 'children',
      'sex' => 'sexes',
      'move' => 'moves',
    );

    $lowercased_word = strtolower($word);
    foreach ($uncountable as $_uncountable) {
      if (substr($lowercased_word, (-1 * strlen($_uncountable))) == $_uncountable) {
        return $word;
      }
    }

    foreach ($irregular as $_plural => $_singular) {
      if (preg_match('/(' . $_singular . ')$/i', $word, $arr)) {
        return preg_replace('/(' . $_singular . ')$/i', substr($arr[0], 0, 1) . substr($_plural, 1), $word);
      }
    }

    foreach ($singular as $rule => $replacement) {
      if (preg_match($rule, $word)) {
        return preg_replace($rule, $replacement, $word);
      }
    }

    return $word;
  }

  /**
   * Converts an underscored or CamelCase.
   */
  public static function titleize($word, $uppercase = '') {
    $uppercase = $uppercase == 'first' ? 'ucfirst' : 'ucwords';
    return $uppercase(Inflector::humanize(Inflector::underscore($word)));
  }

  /**
   * Returns given word as CamelCased.
   */
  public static function camelize($word) {
    return str_replace(' ', '', ucwords(preg_replace('/[^A-Z^a-z^0-9]+/', ' ', $word)));
  }

  /**
   * Converts a word "into_it_s_underscored_version".
   */
  public static function underscore($word) {
    return strtolower(preg_replace('/[^A-Z^a-z^0-9]+/', '_',
      preg_replace('/([a-zd])([A-Z])/', '1_2',
        preg_replace('/([A-Z]+)([A-Z][a-z])/', '1_2', $word))));
  }

  /**
   * Returns a human-readable string from $word.
   */
  public static function humanize($word, $uppercase = '') {
    $uppercase = $uppercase == 'all' ? 'ucwords' : 'ucfirst';
    return $uppercase(str_replace('_', ' ', preg_replace('/_id$/', '', $word)));
  }

  /**
   * Same as camelize but first char is underscored.
   */
  public static function variablize($word) {
    $word = Inflector::camelize($word);
    return strtolower($word[0]) . substr($word, 1);
  }

  /**
   * Converts a class name to its table name according to rails.
   */
  public static function tableize($class_name) {
    return Inflector::pluralize(Inflector::underscore($class_name));
  }

  /**
   * Converts a table name to its class name according to rails.
   */
  public static function classify($table_name) {
    return Inflector::camelize(Inflector::singularize($table_name));
  }

  /**
   * Converts number to its ordinal English form.
   */
  public static function ordinalize($number) {
    if (in_array(($number % 100), range(11, 13))) {
      return $number . 'th';
    }
    else {
      switch (($number % 10)) {
        case 1:
          return $number . 'st';

        case 2:
          return $number . 'nd';

        case 3:
          return $number . 'rd';

        default:
          return $number . 'th';
      }
    }
  }
}
