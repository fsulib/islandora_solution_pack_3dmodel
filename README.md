# islandora_solution_pack_3dmodel
Islandora 3D Model Solution Pack for supporting 3D model data

The Islandora 3D Model Solution Pack (3DSP) is a module for Islandora 7.x that extends its functionality to accommodate the storage and display of 3D models in a variety of formats. By creating a new content model (islandora:3dModelCModel) and zip ingest process, and integrating the Online 3D Viewer, the 3DSP allows repository managers to curate 3D models from any of the following file formats: 

STL 

PLY  

3DM 

OFF 

3DS 

GLB 

FBX 

OBJ 

GLTF 

Online 3D Viewer 

The Online 3D Viewer (O3DV) https://3dviewer.net/ is an open source JavaScript application for displaying a variety of 3D model formats in a browser. The 3DSP integrates this viewer into the page display of 3D models so that when a model is viewed, all relevant files stored by the object are loaded and displayed by the O3DV within the page. 

3D CModel structure 

All Islandora content models define an object as a set of files called “datastreams” which make up that object. Each datastream file is represented by a short all-caps alphanumeric code (such as “MODS” or “TXT”) called the datastream ID, or DSID. Usually, an Islandora object will have one primary asset file associated with it, often in a datastream with the DSID “OBJ”. 

3D models are unique in terms of file format because some (STL, PLY, 3DM & ODF) can be fully contained within a single file, while others (3DS, GLB, FBX) might require any number of supporting image files to properly render. Furthermore, some formats like OBJ and GLTF might require additional mapping files (e.g. .mtl files) which manage the inclusion of the supporting image files. Depending on the format of a 3D model, a single object might only need one datastream or hundreds to properly render.  

The 3D Model CModel (islandora:3dModelCModel) accommodates this range of possibilities for 3D models by defining an object with all the datastreams of standard Islandora objects (MODS, DC, etc.) in addition to as many additional datastreams as the model requires with no defined upper limit. All 3D Model-specific datastreams have a DSID in the form of “MF_” where the underscore represents an integer value, such as “MF0” or “MF1,” to indicate model files 1 and 2, respectively.  

How these various files are managed and rendered by the 3DSP are handled by the dsmap.json file, a well-formed JSON file created by the user while preparing the ingest package and eventually stored in the DSMAP datastream. Since the Online 3D Viewer does not require any differentiation between the files that make up a 3D model, the order of model file datastreams does not matter. However, a best practice to keep long dsmap.json files readable is to sort the model files by importance, with “MF0” representing the primary file, followed by any potential mapping files the object might have, and then all image files last in alphabetical order. Here is an example of a valid dsmap.json file: 

{ 
  "test6.xml": "MODS", 
  "test6.fbx": "MF0", 
  "fsu-seal-full-color123-01.png": "MF2", 
  "iPhone se_.bmp": "MF3", 
  "seeds.jpg": "MF4", 
  "Txt_Aermacchi_M346.tga": "MF5" 
} 

Preparing 3D models for ingest into DigiNole 

3D models being ingested into DigiNole must be compressed into a .zip package.  

To ingest a zip package into Islandora using the 3D Model batch importer, it must contain all the files required to render a 3D model as well as 2 additional files: 

A MODS XML record containing all metadata describing the model 

A JSON map of model file names and what DSID they should be assigned (dsmap.json) 

All files should be stored in the same top-level directory as the other contents of the package. There should not be any sub-directories, as this will break the ingest process.

Note that, unlike other DigiNole ingest packages, every file in the package does not have to have the same name followed by its appropriate extension. As long as the dsmap.json file maps the package contents appropriately, the ingest will work as expected. 

To ingest a 3D model into DigiNole, follow these steps: 

Prepare your ingest package following the instructions in the previous section 

Login to the DigiNole Test admin interface 

Navigate to the appropriate collection 

Click the “Manage” tab 

Click the “Collection” tab 

Click the “Batch Import Objects” button 

Under the “Importer” drop-down menu, make sure “3D Model Zip Importer” is selected and click Next 

Choose the .zip package you would like to ingest. Click Upload and then Import 

A progress bar will display the status of the ingest 

The screen will display the status of the ingest in addition to any error messages if something went wrong 
 
