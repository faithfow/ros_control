<launch>

<rosparam command="load" file="$(find homework03_ws)/yaml/my_yaml.yaml" />
<node pkg="homework03_ws" type="yaml_pub" name="yaml_publisher" output="screen" />
<node pkg="homework03_ws" type="yaml_sub" name="yaml_subscriber" output="screen" />

</launch>