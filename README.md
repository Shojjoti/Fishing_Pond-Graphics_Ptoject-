<h1> 1. Introduction</h1>
<br>
<p> Computer graphics is a course that tech us how to design 2D and 3D images, shapes, scenarios,
and visualizations. In this course we also learnt graph plotting. Whatever we visualize in our
mind, we can plot on the graph first and then create 2D or 3D images using graphics. It’s
something like animation. The main concept of this course is to draw your own imagination
using Computer Graphics. In this course we also learnt about OpenGL platform and GLUT.
Using all these things we finally create a project named “Fishing Pond with scenario
simulation”. The project components are a big fishing pond with fishes, two fisher who are
fishing, a road which covering every sides of the pond, in the scenario we also have a ticket
counter for fishers, in the counter we have a counter man, there are some hills behind the pond,
two lamp post side of the road etc. In this project we have some features like keyboard
functionality, mouse functionality, three seasons (Summer, Winter, Rainy), Day night
conversion.
</p>
<br>
<br>

<h1>2. Objectives</h1>
<br>

<p> The main objective of this project is to </p>
<p> • Understand the basic concepts of computer graphics. </p>
<p>• Understand the basic concepts of OpenGL and GLUT.</p>
<p>• Implement 2D and 3D scenario using OpenGL primitives.</p>
<p>• Understand translation, rotation, and scaling.</p>
<p>• Implement timer function to simulate.</p>
<p>• Implement rain, snowfall, cloud move.</p>

<br>
<br>

<h1>3. Tools and Technologies used </h1> 
<br>
<p>✓ Programming language: C++</p>
<p>✓ Graphics Library: OpenGL</p>
<p>✓ Toolkit: GLUT</p>
<p>✓ Compiler: MinGW/ VS Code</p>
<p>✓ Platform: Windows</p>
<p>✓ Geogebra for plotting points</p>

<h1> 4. System Description</h1>
<br>
<p>The system we developed is mostly a 2D fishing pond environment. But there is also a 3D
component which is the fishing bucket. The main components of the system are:</p>
<br>
<br>

<h3>4.1 Environment</h3>
<br>
<p>▪ Ponds, roads, hills are drawn using polygons and lines.</p>
<p>▪ Frame represents the boundary of the scene.</p>
<p>▪ Day night conversion is implemented by using background color change</p>

<h3>4.2 Fishers</h3>
<p>▪ Two fishers are placed on the same side of the pond.</p>
<p>▪ Fishers are created using circles and polygons.</p>
<p>▪ Fishers can fish using fishing rope.</p>

<h3>4.3 Fishing Rope</h3>
<p>▪ There are two fishing ropes in our project for two fishers.</p>
<p>▪ Fishing ropes are drawn by using DDA Algorithm.</p>

<h3>4.4 Pond</h3>
<p>▪ One big pond was placed in the center.</p>
<p>▪ Pond created using polygon.</p>
<p>▪ In winter the pond becomes ice but in one portion we cut the ice round for fishers. The
circle was made of Bresenham’s Mid-point Circle Algorithm.</p>

<h3>4.5 Ticket counter</h3>
<p>▪ Counter made off using polygons and lines.</p>
<p>▪ People came here to buy tickets for fishing.</p>
<p>▪ There is a list in front of the glass counter. The first line of the list is made of
Bresenham’s Mid-point Line Algorithm.</p>

<h3>4.6 Streetlamp</h3>
<p>▪ There were two streetlamps in our scenario.</p>
<p>▪ These are made off polygons.</p>
<p>▪ In night mode the light brightening by changing color.</p>
<p>▪ In night mode lamps give light. Here the light is drawn by Shading Algorithm.</p>

<h3>4.7 Clouds</h3>
<p>▪ Each cloud is made of three circles.</p>
<p>▪ Clouds simulate through a function.</p>
<p>▪ Cloud changes color depending on seasons.</p>
  
<h3>4.8 Ticket Salesman</h3>
<p>▪ There is one ticket salesman in the counter.</p>
<p>▪ Salesman made of circles, polygons and curve.</p>
<p>▪ Here we did a special thing, the curve is Beizer curve.</p>
  
<h3>4.9 Road Human</h3>
<p>▪ This human is also made of polygons and circles.</p>
<p>▪ The human walking through the road to the counter.</p>
<p>▪ Walking of the human is done by using Translation method.</p>
  
<h3>4.10 Animation control</h3>
<p>▪ To control animations, glutTimerFunc ().</p>
<p>▪ Objects positions are updated over time.</p>
<p>▪ Double buffer is used to avoid flickering.</p>

  <h1>5. Implementation details</h1>
<h3>5.1 Initialization</h3>
<p>The initGL() function initializes the OpenGL environment, sets the background color, defines
the sizes, orthographic projections etc.</p>

<h3>5.2 Display function</h3>
<p>The display () function is responsible for drawing all the components on output. We called too
many draw () functions in our display. It also handles every translation and day night
conversion.</p>

<h3>5.3 Timer Function</h3>
<p>The timer () function updates object positions and toggle between day night mode. We use it
for Rain drop, human moving, clouds moving. This function continuously refreshes the display.</p>

<h3>5.4 Keyboard function</h3>
<p>In our project we use some keyboard functions like for switching Summer to Rainy season just
press the ‘r’ key and for summer to Winter or Rainy to winter just press ‘w’ key.</p>

<h3>5.5 Mouse function</h3>
<p>We used mouse function for day night conversion. For right click it changes to night and for
left click it changes to day.</p>

<h3>5.6 Drawing Techniques</h3>
<p>We used GL_POLYGONS, GL_LINES, GL_QUADS, AND GL_TRIANGLES for drawing
shapes. Circles are drawn using trigonometric functions.</p>

<h1>6. Output description </h1>
<p>The project successfully demonstrated a 2D animated view of a Fishing pond with fishers using
OpenGL. All objects are working properly. Some objects are static and some are dynamic.
Switching between seasons works perfectly. Day night conversion also works successfully.
Every function is working </p>
