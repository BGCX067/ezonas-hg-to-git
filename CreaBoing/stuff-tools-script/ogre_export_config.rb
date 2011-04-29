# Sketchup To Ogre Exporter  Configuration File Version 1.2.0

# Sketchup coords are in inches. The scale value converts inches into ogre units.
# scale = 0.0254  ->  1 ogre unit = 1 meter
# scale = 1       ->  1 ogre unit = 1 inch
# scale = 2.54    ->  1 ogre unit = 1 centimeter
$g_ogre_scale = 0.0254


# If true, meshes will be exported.
$g_ogre_export_meshes = true

#Setting this to true allow the exporter to export also the back faces of the model. It doubles the number of exported triangles.
$ogre_export_backfaces = true

# Destination path for meshes (the *.mesh.xml and *.mesh files end up here).
$g_ogre_path_meshes = "C:\\_export"
#$g_ogre_path_meshes = "/Users/fnunnari/Documents/SketchUpOgreExport"


# If true, materials will be exported.
$g_ogre_export_materials = true

# Destination path for materials (the *.material scripts end up here).
$g_ogre_path_materials = $g_ogre_path_meshes

# Lets you decide whether append the definition of the SketchupDefault material into the materials output.
# Beware that even if this flag is false, the meshes using the default material will be exported in any case. It will be up to you to define the SketchupDefault material somewhere else.
$g_ogre_export_default_material = true


# If true, the exporter will copy all sketchup textures used in the model into the directory set in $g_ogre_path_textures.
$g_ogre_copy_textures = true

# Destination path for textures (all textures end up here if $g_ogre_copy_textures is set to true).
$g_ogre_path_textures = $g_ogre_path_meshes


# If true, auto conversion of xml to binary meshes will be performed,
# using the converter exe specified in $g_ogre_path_xml_converter.
$g_ogre_convert_xml = true

# Path of OgreXmlConverter.exe. This is required to convert xml meshes into binary .mesh files.
$g_ogre_path_xml_converter = "C:\\Ogre172\\bin\\release\\OgreXmlConverter.exe"
#$g_ogre_path_xml_converter = "/Users/fnunnari/Documents/OgreCommandLineTools/OgreXmlConverter"


# Allow to apply a unique id at each export in order to avoid name conflicts among different exports of the same object.
# The unique id is applied as prefix to material names and to textures.
# The prefix is an integer calculated as the number of seconds from 1 Jan 1970. It works as long as you don't export more than 1 object per second ;-)
$g_ogre_prepend_unique_prefix = true

