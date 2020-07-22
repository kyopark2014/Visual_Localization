# Visual_Localization

It shows a simplified object localization algorithm using multiple cameras. This use a parallel projection model which supports both zooming and panning of the imaging devices. The algorithm is based on a virtual viewable plane for creating a relationship between an object position and a reference coordinate. The reference point is obtained from a rough estimate which may be obtained from the preestimation process. The algorithm minimizes localization error through the iterative process with relatively low-computational complexity. In addition, nonlinearity distortion of the digital image devices is compensated during the iterative process. Finally, the performances of several scenarios are evaluated and analyzed in both indoor and outdoor environments.

Ths picture shown as bellow illustrates the application model where multiple people are localized in a multiple-camera environment. The cameras can freely move with zooming and panning capabilities. Within a tracking environment, the method uses detected object points to find object location.
![image](https://user-images.githubusercontent.com/52392004/88118798-8b256380-cbf9-11ea-8f89-df30f699541e.png)

### Basic Flow

The individual panning factors is respected to a global coordinate.

![image](https://user-images.githubusercontent.com/52392004/88119005-24547a00-cbfa-11ea-8e55-6c3e4cd88c45.png)


When each cameras are detecting objects, the location was localized based on this algorithm then displayed in the layout diagram. 
![image](https://user-images.githubusercontent.com/52392004/88089881-babb7800-cbc7-11ea-8400-86200ef0c35f.png)

### Example
#### Camera1
![cam1](https://user-images.githubusercontent.com/52392004/88090247-459c7280-cbc8-11ea-8d97-77092fa8dd00.gif)
#### Camera2
![cam2](https://user-images.githubusercontent.com/52392004/88090261-47fecc80-cbc8-11ea-8f55-e381eeebe0a9.gif)
#### The coordinates of objects
![traj](https://user-images.githubusercontent.com/52392004/88090268-4af9bd00-cbc8-11ea-8362-df0172651328.gif)

### Reference
https://link.springer.com/content/pdf/10.1155/2008/256896.pdf
