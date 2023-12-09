<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="content-type" content="text/html;charset=utf-8">
    <meta name="viewport" content="width=device-width, user-scalable=no">
    <title>Online 3D Viewer</title>

    <!-- website libs start -->
    <link rel="stylesheet" type="text/css" href="libs/pickr.monolith.min.css">
    <script type="text/javascript" src="libs/pickr.es5.min.js"></script>
    <!-- website libs end -->

    <!-- meta start -->
    <!-- meta end -->

    <!-- website start -->
    <link rel="stylesheet" type="text/css" href="css/icons.css">
    <link rel="stylesheet" type="text/css" href="css/themes.css">
    <link rel="stylesheet" type="text/css" href="css/core.css">
    <link rel="stylesheet" type="text/css" href="css/controls.css">
    <link rel="stylesheet" type="text/css" href="css/dialogs.css">
    <link rel="stylesheet" type="text/css" href="css/treeview.css">
    <link rel="stylesheet" type="text/css" href="css/panelset.css">
    <link rel="stylesheet" type="text/css" href="css/navigator.css">
    <link rel="stylesheet" type="text/css" href="css/sidebar.css">
    <link rel="stylesheet" type="text/css" href="css/website.css">
    <link rel="stylesheet" type="text/css" href="css/embed.css">
    <script type="text/javascript" src="o3dv.website.min.js"></script>

    <script type="text/javascript">
        OV.StartWebsite ('libs');
    </script>
</head>

<body>
    <input type="file" id="open_file" style="display:none;" multiple></input>
    <div class="header" id="header">
        <div class="title" style="display: none;">
            <div class="title_left">
                <a href="index.html">
                    <svg class="logo_image"><use href="assets/images/3dviewer_net_logo_text.svg#logo"></use></svg>
                </a>
            </div>
            <div class="title_right" id="header_buttons"></div>
            <div class="main_file_name only_full_width" id="main_file_name"></div>
        </div>
        <div class="toolbar" id="toolbar"></div>
    </div>
    <div class="main" id="main">
        <div class="main_left_container only_full_width" id="main_left_container">
            <div class="main_navigator ov_panel_set_container" id="main_navigator"></div>
            <div class="main_splitter" id="main_navigator_splitter"></div>
        </div>
        <div class="main_viewer" id="main_viewer"></div>
        <div class="main_right_container only_full_width" id="main_right_container">
            <div class="main_splitter" id="main_sidebar_splitter"></div>
            <div class="main_sidebar ov_panel_set_right_container" id="main_sidebar"></div>
        </div>
    </div>
    <div class="intro ov_thin_scrollbar" id="intro">
        <div class="intro_section only_full_width only_full_height">
            <svg class="intro_logo"><use href="assets/images/3dviewer_net_logo.svg#logo"></use></svg>
        </div>
        <div class="intro_section intro_big_text">
            Drag and drop 3D models here.<br>
            <b>obj, 3ds, stl, ply, gltf, 3dm, fbx, <a target="_blank" href="info/index.html">and more</a></b>
        </div>
        <div class="intro_section">
            <div>Example models:</div>
            <div class="example_models">
                <a href="index.html#model=assets/models/solids.obj,assets/models/solids.mtl">solids</a>
                <span style="color:#aaaaaa;"> | </span>
                <a href="index.html#model=assets/models/car.glb">car</a>
                <span style="color:#aaaaaa;"> | </span>
                <a href="index.html#model=assets/models/DamagedHelmet.glb">helmet</a>
            </div>
        </div>
        <!-- intro start -->
        <!-- intro end -->
    </div>
</body>

</html>
