<?php
/**
 * Inc file contains the functions
 */

/**
 * main function for generate programSectionPageFeed xml feed
 *
 * @return array
 */

function programSectionPageFeed() {
  //check into redis
   //$redis_key = "itgd_programSectionPageFeed";
   //$result_get = getRedis($redis_key);

   //if($result_get['key_value'] !=""){
    //   $output = $result_get['key_value'];
       //echo "redis get - ". $output; exit();
   //}
   //else{
  // variable declation
  global $base_url;
  $output = "";
  $ttl = 300;
  // tid conf function
  $conf_array = tidConfig();
  $section_list = array();
  $section_list_story = array();
  $term_list = array();
  $node_count = 0;
  $term_name = "";
  $term_url = "";
  $file_name = "";
  $cat_icon_img = "";

  $listcount = 0;
  $return_flag = "";

  // get section list
  //$section_list = categoryManagerSectionTid('story');
  $section_list = $conf_array['program_sec_tid'];
  //fatch & write xml node of all vedio main cat
  foreach ($section_list as $key => $value) {
    // check section is story
    $node_count = customNodeCount('videogallery', $value);
    //check section have category
    //$term_list = taxonomy_get_tree(14, $value, $max_depth = NULL, $load_entities = FALSE);
    if ($node_count > 0 ) {

      $term = taxonomy_term_load($value);
      $term_name = $term->name;
      $term_url = nodeCategoryFrontUrl($value, 'term');
      $child_term_url = nodeCategoryFrontUrl($value, 'term');

      $term_name = drupal_strtolower(str_replace(" ", "-", $term_name));
      $term_name = drupal_strtolower(str_replace("&", "and", $term_name));
      $term_file_name = $term_name . ".xml";
      // section xml feed file name
        $listcount++;
        $cat_icon_img = sectionCategoryIconImg($value);
        // child xml node
        $child_node .= "\n<item>
                            <title><![CDATA[" . $term_name . "]]></title>
                            <url>" . $term_file_name . "</url>
                            <weburl><![CDATA[" . $base_url . "/" . $child_term_url . "]]></weburl>
                            <sectionimage>" . $cat_icon_img . "</sectionimage>
                          </item>";

    }
  }
 //write xml node of storysectionlisting
  if ($child_node) {
        // xml feed header
        $output .= program_section_page_feed_header();
        $output .= "\n<id>1</id>
                            <title><![CDATA[programmes]]></title>
                            <itemcount>" . $listcount . "</itemcount>\n";
        // child node
        $output .= $child_node;
        // xml feed footer
        $output .= "\n" . program_section_page_feed_footer();
      }
       // set into redis
    //$result_set = setRedis($redis_key, $output, $ttl);
    //echo "redis set - ". $result_set['set_flag']; exit();
   //}
 // write xml file - storysectionlisting.xml

  if ($output) {
        //$term_feed_path = getcwd() . "/sites/all/modules/custom/itg_mobile_feed/xml_it/videos";
        $term_feed_path = "public://xml_it/videos";
		   file_prepare_directory($term_feed_path, FILE_CREATE_DIRECTORY);
        $file_name = "programmes.xml";
        $return_flag .= writeFeedFile($term_feed_path, $file_name, $output);
      }
  //return $return_flag;
  header('Content-Type: application/xml; charset=utf-8');
  echo $output;  die();
}
