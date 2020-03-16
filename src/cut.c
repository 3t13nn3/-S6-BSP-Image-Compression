#include "cut.h"

Cut newCutFromPoints(Point a, Point b, Point c, Point d){

    Cut toReturn;

    toReturn._coordinates[0] = a;
    toReturn._coordinates[1] = b;
    toReturn._coordinates[2] = c;
    toReturn._coordinates[3] = d;

    return toReturn;
}


/*
Subset representation:
        ^  5--------------6
        Z /|             /|
         / |    X>      / |
        1--------------2  |
        |  7-----------|--8
      Y | /            | /
     \/ |/             |/
        3--------------4   
*/
Cut getCutFromSubset(Subset * sub, int cutAxe) {
    
    //must affect them to avoid warnings --'
	Point a = newPoint(0,0,0);
    Point b = newPoint(0,0,0);
    Point c = newPoint(0,0,0);
    Point d = newPoint(0,0,0);

    //According to x=(1−T)a+c & y=(1−T)b+d formulas to find a point on a segment in function of a ratio
    //actually T is the ratio as T ∈ [0;1] & 2 points (a,b) and (c,b)...
    //we are using totalDistance/2 as newPointDiscance value because we are cutting our space by half, but we could addapt it for the portion we want
    float totalDistance, newPointDistance, T;

	switch (cutAxe){
    case X_AXE:

        totalDistance = sub->_coordinates[1]._x - sub->_coordinates[0]._x;
	    newPointDistance = totalDistance/2;

	    T = newPointDistance/totalDistance;

        int x = (1 - T) * sub->_coordinates[0]._x + T * sub->_coordinates[1]._x;

		a._x = x;
		a._y = sub->_coordinates[0]._y;
		a._z = sub->_coordinates[0]._z;

        b._x = x;
		b._y = sub->_coordinates[4]._y;
		b._z = sub->_coordinates[4]._z;

        c._x = x;
		c._y = sub->_coordinates[2]._y;
		c._z = sub->_coordinates[2]._z;

        d._x = x;
		d._y = sub->_coordinates[6]._y;
		d._z = sub->_coordinates[6]._z;

		break;

	case Y_AXE:

        totalDistance = sub->_coordinates[2]._y - sub->_coordinates[0]._y;
	    newPointDistance = totalDistance/2;

	    T = newPointDistance/totalDistance;

        int y = (1 - T) * sub->_coordinates[0]._y + T * sub->_coordinates[2]._y;

		a._x = sub->_coordinates[0]._x;
		a._y = y;
		a._z = sub->_coordinates[0]._z;

        b._x = sub->_coordinates[1]._x;
		b._y = y;
		b._z = sub->_coordinates[1]._z;

        c._x = sub->_coordinates[4]._x;
		c._y = y;
		c._z = sub->_coordinates[4]._z;

        d._x = sub->_coordinates[5]._x;
		d._y = y;
		d._z = sub->_coordinates[5]._z;

		break;

	case Z_AXE:

        totalDistance = sub->_coordinates[4]._z - sub->_coordinates[0]._z;
	    newPointDistance = totalDistance/2;

	    T = newPointDistance/totalDistance;

        int z = (1 - T) * sub->_coordinates[0]._z + T * sub->_coordinates[4]._z;

		a._x = sub->_coordinates[0]._x;
		a._y = sub->_coordinates[0]._y;
		a._z = z;

		b._x = sub->_coordinates[1]._x;
		b._y = sub->_coordinates[1]._y;
		b._z = z;


        c._x = sub->_coordinates[2]._x;
		c._y = sub->_coordinates[2]._y;
		c._z = z;

        d._x = sub->_coordinates[3]._x;
		d._y = sub->_coordinates[3]._y;
		d._z = z;

		break;

	default:
		break;
	}

	return newCutFromPoints(a, b, c, d);
}

void printCut(int indentation, Cut * c){

	int i;
	for(i=0; i<indentation; ++i){
		printf("\t");
	}
	printf("Cut:\n");
    for(i = 0; i < CUT_POINTS_SIZE; ++i){
        printPoint(indentation+1,&c->_coordinates[i]);
    }

	printf("\n");
}
