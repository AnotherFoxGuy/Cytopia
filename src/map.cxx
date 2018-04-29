#include "map.hxx"

Map::Map(SDL_Renderer* renderer, SDL_Window *window)
{
  int tilesize = 32;
  _floorTilesMatrix = vectorMatrix(_width, _height);
  _gridTilesMatrix = vectorMatrix(_width, _height);
  _buildingsTilesMatrix = vectorMatrix(_width, _height);



  // Default: Floor and Buildings are drawn
  _activeLayers = LAYER_FLOOR | LAYER_BUILDINGS;


  SDL_GetWindowSize(window, &_screen_width, &_screen_height);
  // 16 x 16 height for further tests

  const int height = 16;
  const int width = 16;

  int mapp[height][width] = {
    { 1,1,0,2,2,2,2,2,1,1,2,2,2,2,2,1 },
  { 1,1,1,1,2,1,1,2,1,1,2,2,2,2,2,1 },
  { 2,1,1,0,2,2,2,2,1,1,2,2,2,2,2,1 },
  { 2,1,1,2,2,1,1,2,1,1,2,2,2,2,2,1 },
  { 2,1,1,4,4,4,1,2,1,1,2,2,2,2,4,1 },
  { 2,1,1,4,4,4,1,2,1,1,2,2,2,2,2,1 },
  { 2,1,1,4,4,4,1,2,1,1,2,2,4,2,2,1 },
  { 2,2,2,4,4,4,2,1,2,3,3,3,4,2,2,1 },
  { 1,1,2,2,2,2,2,3,4,3,3,3,4,2,2,2 },
  { 1,1,1,1,2,1,1,2,1,3,3,3,2,2,2,3 },
  { 2,1,1,1,2,2,2,2,1,1,2,2,2,2,2,1 },
  { 2,1,1,2,2,1,1,2,1,1,3,2,2,2,4,4 },
  { 2,1,1,4,2,1,1,2,1,1,3,2,2,2,2,4 },
  { 2,1,1,1,2,1,1,2,1,1,3,3,3,3,3,4 },
  { 2,1,1,1,1,1,1,2,1,1,2,2,2,2,4,4 },
  { 2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,1 }
  };






  for (int x = 0; x <= _width; x++)
  {
    for (int y = _height; y >= 0; y--)
    {
      Sprite *tile = nullptr;
      Sprite *grid = nullptr;
      Sprite *building = nullptr;
      
      tile = new Sprite("resources/images/city/floor.png", Point(x, y), renderer, window);
    
      grid = new Sprite("resources/images/city/grid.png", Point(x, y), renderer, window);
      
      
      if ( (x == 1) && (y == 1) )
        building = new Sprite("resources/images/city/house.png", Point(x, y), renderer, window);
      
      _floorTilesMatrix.addSprite(x, y, tile);
      _gridTilesMatrix.addSprite(x, y, grid);
      _buildingsTilesMatrix.addSprite(x, y, building);
    }
  }
}

Map::~Map()
{
  // TODO Auto-generated destructor stub
}


void Map::parseMapFile()
{
  // TODO: load Map from FIle. Coordinates, Height, Tile
}

void Map::render()
{
  int i = 0;
  int y = 0;
  int x = 0;

  for (int x = 0; x <= _width; x++)
  {
    for (int y = _height; y >= 0; y--)
    {
      // Layer 0 - floor
      if ( _activeLayers & LAYER_FLOOR )
      {
        if ( _floorTilesMatrix.getSprite(x, y) != nullptr )
          _floorTilesMatrix.getSprite(x, y)->render(_cameraOffset, _zoom);
      }
      // Layer 1 - grid
      if ( _activeLayers & LAYER_GRID )
      {
        if ( _gridTilesMatrix.getSprite(x, y) != nullptr )
          _gridTilesMatrix.getSprite(x, y)->render(_cameraOffset, _zoom);
      }
      // Layer 2 - Buildings
      if ( _activeLayers & LAYER_BUILDINGS )
      {
        if ( _buildingsTilesMatrix.getSprite(x, y) != nullptr )
          _buildingsTilesMatrix.getSprite(x, y)->render(_cameraOffset, _zoom);
      }
    }
  }
}


/// convert Screen Coordinates to Iso Coordinates
Point Map::getIsoCoords(Point screenCoordinates, bool calcWithoutOffset)
{
  Point isoCoordinates;
  int x, y;

  if (calcWithoutOffset)
  {
    x = (screenCoordinates.getX() + 2.0*(screenCoordinates.getY())) / (TILE_SIZE*_zoom) - 1.5;
    y = (screenCoordinates.getX() - 2.0*(screenCoordinates.getY())) / (TILE_SIZE*_zoom) + 1.5;
  }
  else
  {
    x = (screenCoordinates.getX() + _cameraOffset.getX() + 2.0*(screenCoordinates.getY() + _cameraOffset.getY())) / (TILE_SIZE*_zoom) - 1.5;
    y = (screenCoordinates.getX() + _cameraOffset.getX() - 2.0*(screenCoordinates.getY() + _cameraOffset.getY())) / (TILE_SIZE*_zoom) + 1.5;
  }
  isoCoordinates.setCoords(x, y);
  return isoCoordinates;
}

/// convert Iso Coordinates to Screen Coordinates
Point Map::getScreenCoords(Point isoCoordinates, bool calcWithoutOffset)
{
  Point screenCoordinates;
  int x, y;

  if ( calcWithoutOffset )
  {
    x = (TILE_SIZE*_zoom * isoCoordinates.getX() * 0.5) + (TILE_SIZE*_zoom * isoCoordinates.getY() * 0.5);
    y = (TILE_SIZE*_zoom * isoCoordinates.getX() * 0.25) - (TILE_SIZE*_zoom * isoCoordinates.getY() * 0.25);
  }
  else
  {
    x = (TILE_SIZE*_zoom * isoCoordinates.getX() * 0.5) + (TILE_SIZE*_zoom * isoCoordinates.getY() * 0.5) - _cameraOffset.getX();
    y = ((TILE_SIZE*_zoom * isoCoordinates.getX() * 0.25) - (TILE_SIZE*_zoom * isoCoordinates.getY() * 0.25)) - _cameraOffset.getY();
  }
  screenCoordinates.setCoords(x, y);
  return screenCoordinates;
}

void Map::centerScreenOnPoint(Point isoCoordinates)
{
  Point screenCoordinates = getScreenCoords(isoCoordinates, true);
  int x, y;

  x = (screenCoordinates.getX() + (TILE_SIZE*_zoom)*0.5) - _screen_width * 0.5;
  y = (screenCoordinates.getY() + (TILE_SIZE*_zoom)*0.75) - _screen_height * 0.5;
  
  _cameraOffset.setCoords(x, y);
}

Point Map::getCameraOffset() 
{ 
  return _cameraOffset; 
}

// Check if Point is with map boundaries

bool Map::checkBoundaries(Point isoCoordinates)
{
  if ( (isoCoordinates.getX() >= 0 && isoCoordinates.getX() <= _width) && (isoCoordinates.getY() >= 0 && isoCoordinates.getY() <= _height) )
    return true;
  else
    return false;
}

float Map::getZoomLevel() 
{ 
  return _zoom; 
}

void Map::setZoomLevel(float zoomLevel) 
{ 
  _zoom = zoomLevel; 
}

void Map::setCameraOffset(Point offset) 
{ 
  _cameraOffset = offset; 
}

void Map::findNeighbors(Point isoCoords)
{
  _floorTilesMatrix.findNeighbors(isoCoords.getX(), isoCoords.getY());
}

void Map::enableLayer(unsigned int layer)
{
  // Turn on by using bitwise OR
  _activeLayers |= layer;
}

void Map::disableLayer(unsigned int layer)
{
  // Turn off by using bitwise AND with inversed pattern
  _activeLayers &= ~layer;
}


void Map::toggleLayer(unsigned int layer)
{
  // Toggle bitmask by using bitmask XOR
  _activeLayers ^= layer;
}