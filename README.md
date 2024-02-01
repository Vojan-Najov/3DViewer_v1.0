# 3DViewer_v1.0

Implementation a program to view 3D wireframe models. Qt, OpenGL.

## Subject

- [Subject EN](misc/docs/subject_en.md)
- [Subject_RU](misc/docs/subject_ru.md)

## Usage

- `$>make install`
- The lib3Dviewer.a library is written in C, a graphical user interface by means of Qt6, graphics for displaying models using OpenGL API 2.1.
- The program supports model descriptions in Wavefront obj format.
- To load the model, click on the menu bar File->open. The program works with one model at a time.
- The upper-left corner displays information about the name of the selected file, the number of vertices and edges in the model.
- The panel on the right shows buttons for shifting and rotating the model along three coordinate axes, and buttons for changing the scale.
- The panel on the right contains buttons to customize the display of the model, such as changing the background colors, vertices and faces, the type and size of lines and vertices. You can also choose the type of projection: central or parallel.
- The program settings are saved in a file .3DViewer_config in the user's home directory between program restarts.
- In the File->save menu, you can save the current model as an obj file, jpeg file, or bmp file. By default, it is saved in obj format, for jpeg and bmp formats, you need to explicitly specify the file extension.
- A gif file recording function is also available. \
  <img src="./misc/images/example_01.png" alt="example_01" width="700"/> \
  ![example](https://github.com/Vojan-Najov/3DViewer_v1.0/blob/main/misc/images/example.gif)

