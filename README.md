### Simple image editor
This is a simple image editor that currently supports two transformations: 
* 90 degree rotation
* b&w filter

The only format currently supported is BMP.
To add new actions or formats no code has to be rewritten. 

For a new format you have to:
* write functions that transfer the image from a new format to the internal image presentation and vice versa
* add these functions to [formats.h](./formats/formats.h)

To add a new transformation:
* write a function that applies the transformation to the internal image presentation
* add this function to [actions.h](./actions/actions.h)

