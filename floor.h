#ifndef FLOOR_H
#define FLOOR_H

#define FLOOR_0 0
#define FLOOR_1 1

class Floor {
private:
  GLuint texture;
  int activeFloor;

public:
  void draw();
  void load(int activeFloor);
  void switchFloor();
  
  int getactiveFloor();
};


GLuint LoadTextureRAW( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 255;
    height = 255;
    data = (BYTE*) malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
}

int Floor::getactiveFloor(){return activeFloor; }

void Floor::switchFloor() {activeFloor = 0;}

void Floor::load(activeFloor) {
switch (activeFloor) {
  case FLOOR_0: {texture = LoadTextureRAW("C:\\Users\\João Silva\\Desktop\\lab10\\texture2.raw", 1); break;}
  case FLOOR_1: {texture = LoadTextureRAW("C:\\Users\\João Silva\\Desktop\\lab10\\wood.bmp", 1); break;}
}}

void Floor::draw() {
   glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f); 
    // GLfloat floorColorA[] = {0.10f, 0.10f, 0.10f, 1.0f};
    // GLfloat floorColorD[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat floorColorA[] = {0.10f, 0.10f, 0.10f, 1.0f};
    GLfloat floorColorD[] = {0.55f, 0.55f, 0.55f, 1.0f};
    GLfloat floorColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat floorColorS[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, floorColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floorColorD);
    glMaterialfv(GL_FRONT, GL_EMISSION, floorColorE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, floorColorS);
    glMaterialf(GL_FRONT, GL_SHININESS, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    float i, j, k, l, m = 0.5f, n = m*1/28.0f, o = m*1/32.0f;
    glBegin(GL_QUADS);
    for (i = 0.0f, k = 0.0f; i < 28.0f; i+= m, k += n) {
      for (j = 0.0f, l = 0.0f; j < 32.0f; j+= m, l += o) {
        glTexCoord2f(k, l);
        glVertex3f(i, j, 0.0f);
        glTexCoord2f(k+n, l);
        glVertex3f(i + m, j, 0.0f);
        glTexCoord2f(k+n, l+o);
        glVertex3f(i + m, j + m, 0.0f);
        glTexCoord2f(k, l+o);
        glVertex3f(i, j + m, 0.0f);
      }
    }
    glEnd();
    
  // glBegin(GL_QUADS);
    // glTexCoord2f(0.0, 0.0);
    // glVertex3f(0.0f, 0.0f, 0.0f);
    // glTexCoord2f(0.0, 1.0);
    // glVertex3f(0.0f, 32.0f, 0.0f);
    // glTexCoord2f(1.0, 1.0);
    // glVertex3f(28.0f, 32.0f, 0.0f);
    // glTexCoord2f(1.0, 0.0);
    // glVertex3f(28.0f, 0.0f, 0.0f);
  // glEnd();

  glDisable(GL_TEXTURE_2D);
    
  glPopMatrix();
}

#endif
