

// create the mesh corresponding to a circle centered at origin and
var createCircle = function(){
    // create the geometry: vertices and faces
    let geometryCircle = new THREE.RingGeometry(0.988,1.012,10000); // store the vertices and faces of the circle (ring with same inner and outer radius) ,
    // the third argument is the number of segments of the curves (kind of resolution of the circle)

    // create the corresponding material
    let materialCircle = new THREE.MeshBasicMaterial({color: forestGreen, side: THREE.DoubleSide});

    // create the mesh from the vertices,faces and material
    return new THREE.Mesh(geometryCircle,materialCircle);
}


var createPoint = function(x,y,z,color){
    // geometry that will contain the vertices and colors
    // the material will contain the thickness of the points
    let geometryPoint = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.1, vertexColors: true});

    geometryPoint.vertices.push(new THREE.Vector3(x,y,z));
    geometryPoint.colors.push(color);

    return new THREE.Points(geometryPoint,materialPoints);
}







// line defined by a normal vector passing through the origin
var createLine = function (unitNormalVector,XminScene,XmaxScene) {
    var points = [];
    points.push( new THREE.Vector3( XminScene, (-unitNormalVector[2]*unitNormalVector[2] - (unitNormalVector[0]*XminScene))/unitNormalVector[1], unitNormalVector[2] ) );
    points.push( new THREE.Vector3( 0.0, 0.0, unitNormalVector[2] ) );
    points.push( new THREE.Vector3( XmaxScene, (-unitNormalVector[2]*unitNormalVector[2] - (unitNormalVector[0]*XmaxScene))/unitNormalVector[1], unitNormalVector[2] ) );

    var geometryLine = new THREE.BufferGeometry().setFromPoints( points );
    var materialLine = new THREE.LineBasicMaterial({color: 0x0000ff});

    return new THREE.Line( geometryLine, materialLine )
}

// line defined from
var createLineFromTwoPoints = function (pt1,pt2) {
    let geometryLine = new THREE.Geometry();
    geometryLine.vertices.push(new THREE.Vector3( pt1[0], pt1[1], 0));
    geometryLine.vertices.push(new THREE.Vector3( pt2[0], pt2[1], 0));

    var materialLine = new THREE.LineBasicMaterial({color: 0x0000ff});

    return new THREE.LineSegments(geometryLine, materialLine);
}


// define the axis of the scene with two lines
var createXYAxis = function (XminScene,XmaxScene) {

    let unitNormalVector=[0.0,1.0,0.0];
    var points = [];
    points.push( new THREE.Vector3( XminScene, (-unitNormalVector[2]*unitNormalVector[2] - (unitNormalVector[0]*XminScene))/unitNormalVector[1], unitNormalVector[2] ) );
    points.push( new THREE.Vector3( 0.0, 0.0, unitNormalVector[2] ) );
    points.push( new THREE.Vector3( XmaxScene, (-unitNormalVector[2]*unitNormalVector[2] - (unitNormalVector[0]*XmaxScene))/unitNormalVector[1], unitNormalVector[2] ) );

    var pointsY = [];
    pointsY.push( new THREE.Vector3( 0.0, -1.0, unitNormalVector[2] ) );
    pointsY.push( new THREE.Vector3( 0.0, 0.0, unitNormalVector[2] ) );
    pointsY.push( new THREE.Vector3( 0.0, 1.0, unitNormalVector[2] ) );


    var geometryLineXaxis = new THREE.BufferGeometry().setFromPoints( points );
    var geometryLineYaxis = new THREE.BufferGeometry().setFromPoints( pointsY );
    var materialLine = new THREE.LineBasicMaterial({color: 0xff00ff});

    return [new THREE.Line( geometryLineXaxis, materialLine ),new THREE.Line( geometryLineYaxis, materialLine )]
}






