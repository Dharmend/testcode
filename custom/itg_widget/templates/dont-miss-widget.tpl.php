<?php if (!empty($data)) : global $base_url; ?>
  <div class="dont-miss">
    <ul>
      <?php foreach ($data as $key => $node_data) { ?>
        <li class="dont-miss-listing" id="dont-miss-<?php print $key ?>">
          <?php if (!empty($node_data['si_file_uri']) && file_exists($node_data['si_file_uri'])) { ?>
            <div class="dm-pic">
              <a title="<?php echo $node_data['title'] ?>" href="<?php echo $base_url . '/' . drupal_get_path_alias("node/" . $node_data['nid']) ?>">
                <?php $file_uri = image_style_url("image170x127", $node_data['si_file_uri']);
                ?>
                  <img src="<?php print $file_uri; ?>" alt="<?php echo $node_data['field_story_small_image_alt'] ?>" title="<?php echo $node_data['field_story_small_image_title'] ?>" />
              </a>
            </div>
            <?php
          }
          else {
            ?>
            <div class="dm-pic">
              <a href="<?php echo $base_url . '/' . drupal_get_path_alias("node/" . $node_data['nid']) ?>">
                <img width="170" height="127" src="<?php print $base_url . '/' . drupal_get_path('theme', 'itg'); ?>/images/itg_image170x127.jpg" alt="" />
              </a>
            </div>
          <?php } ?>

          <div class="dm-detail">

            <?php if (!empty($node_data['extra'])) : ?>
              <h4><?php print $node_data['extra']; ?></h4>
            <?php endif; ?>

            <?php if (!empty($node_data['title'])) : ?>    
              <p class="dont-miss-widget dont-miss-<?php echo $node_data['nid'] ?>">
                <?php 
                if(function_exists('itg_common_get_smiley_title')) {
                  echo l(itg_common_get_smiley_title($node_data['nid'], 0, 60), "node/" . $node_data['nid'] , array('html' => TRUE , "attributes" => array("title" =>$node_data['title'])));
                } else {
                  echo l(mb_strimwidth($node_data['title'], 0, 70, ".."), "node/" . $node_data['nid'] , array("attributes" => array("title" =>$node_data['title'])));
                }
                ?>
              </p>
            <?php endif; ?>

          </div>
        </li>
      <?php } ?>
    </ul>
  </div>
<?php else : ?>
  <span class="no-result-found"><?php print t("Content Not Found") ?></span>
<?php endif; ?>
