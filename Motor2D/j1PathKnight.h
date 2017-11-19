#ifndef __j1PATHKNIGHT_H__
#define __j1PATHKNIGHT_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "p2List.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 1041

// --------------------------------------------------
// Recommended reading:
// Intro: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Details: http://theory.stanford.edu/~amitp/GameProgramming/
// --------------------------------------------------

class j1PathKnight : public j1Module
{
public:

	j1PathKnight();

	// Destructor
	~j1PathKnight();

	// Called before quitting
	bool CleanUp();

	// Sets up the walkability map
	void SetMap(uint width, uint height, uchar* data);

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);

	// To request all tiles involved in the last generated path
	const p2DynArray<iPoint>* GetLastPath() const;

	// Utility: return true if pos is inside the map boundaries
	bool CheckBoundaries(const iPoint& pos) const;

	// Utility: returns true is the tile is walkable
	bool IsWalkable(const iPoint& pos) const;

	// Utility: return the walkability value of a tile
	uchar GetTileAt(const iPoint& pos) const;

private:

	// size of the map
	uint width;
	uint height;
	// all map walkability values [0..255]
	uchar* map;
	// we store the created path here
	p2DynArray<iPoint> last_path;
};

// forward declaration
struct PathListKnight;

// ---------------------------------------------------------------------
// Pathnode: Helper struct to represent a node in the path creation
// ---------------------------------------------------------------------
struct PathNodeKnight
{
	// Convenient constructors
	PathNodeKnight();
	PathNodeKnight(int g, int h, const iPoint& pos, const PathNodeKnight* parent);
	PathNodeKnight(const PathNodeKnight& node);

	// Fills a list (PathList) of all valid adjacent pathnodes
	uint FindWalkableAdjacents(PathListKnight& list_to_fill) const;
	// Calculates this tile score
	int Score() const;
	// Calculate the F for a specific destination tile
	int CalculateF(const iPoint& destination);

	// -----------
	int g;
	int h;
	iPoint pos;
	const PathNodeKnight* parent; // needed to reconstruct the path in the end
};

// ---------------------------------------------------------------------
// Helper struct to include a list of path nodes
// ---------------------------------------------------------------------
struct PathListKnight
{
	// Looks for a node in this list and returns it's list node or NULL
	p2List_item<PathNodeKnight>* Find(const iPoint& point) const;

	// Returns the Pathnode with lowest score in this list or NULL if empty
	p2List_item<PathNodeKnight>* GetNodeLowestScore() const;

	// -----------
	// The list itself, note they are not pointers!
	p2List<PathNodeKnight> list;
};



#endif // __j1PATHFINDINGKNIGHT_H__