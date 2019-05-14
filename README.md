# xyz2xza
converter for 3D printer Slic3r vase mode to CNC with A axis
Takes in GCode generated from Slic3r vase mode no bottom layer no top layer.
A few restricting issues. 

-Cannot detect collisions
-Cannot cross (0,0)
-Slic3r center must be set to (0,0)
-Resolution of the crawl must be set (CRAWL_RESOLUTION=0.5 mm) Smaller the better but too small will make the resulting code really large

to do:  
- Add Pre settings
- Add Post settings

Usage: xyz2xza input.gcode > out.ngc

it strips all which is not G1 from original 
