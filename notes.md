# Loading an image to the screen
GrBitBlt(destination, destX, destY,
         source, sourceLeft, sourceTop, sourceRight, sourceBottom,
         operation);

# Getting image size before loading
GrQueryPnm(path, &width, &height, &maxval)