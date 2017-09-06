# 3d-face-modeling-depth
3d face modeling from a depth stream (RGBD)

Release an open-source software for generating person-specific 3D face models. A 3D face model is a mesh structure representing a person’s 3D geometrical shape. The software will use a Microsoft Kinect-like sensor, which provides a classical image along with distance to the camera (range data). A user must stand in front of the camera and move its head freely. The software will process the video stream of the sensor to generate the user’s 3D face. 

Since each frame of the sensor is low-resolution and quite noisy, conventional methods provide models that cannot be used for practical applications. Our software smartly denoises the data and presents state-of-the-art near laser-scan quality models. The program runs in real-time.

Applications may include gaming, entertainment, virtual try-on, avatar, biometrics, medical, etc. For instance, plastic surgeons can generate an accurate model of their patient and manipulate the mesh to simulate medical procedures and showcase the expected post-surgery results.
