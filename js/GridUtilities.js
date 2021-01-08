let forestGreen = new THREE.Color(0x009900);
let deepBlue = new THREE.Color(0x3774CB);
let deepRed = new THREE.Color(0x721606);
let red = new THREE.Color(0xff0000);

var createDigitalPoint = function(x,y,z,color){
    // geometry that will contain the vertices and colors
    // the material will contain the thickness of the points
    let geometryPoint = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.1, vertexColors: true});

    geometryPoint.vertices.push(new THREE.Vector3(x,y,z));
    geometryPoint.colors.push(color);

    return new THREE.Points(geometryPoint,materialPoints);
}


var createGrid = function(N){
    // geometry that will contain the vertices and colors of the digital grid
    // better if N is odd
    let geometryPoint = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.18, vertexColors: true});

    // loop over a set of digital points
    for(let i=0;i<N;i++){
        for(let j=0;j<N;j++) {
            let x = j-(~~(N/2));
            let y = i-(~~(N/2));
            geometryPoint.vertices.push(new THREE.Vector3(x, y, 0));
            geometryPoint.colors.push(deepBlue);
        }
    }
    return new THREE.Points(geometryPoint,materialPoints);
}

var createCells = function(N,min,max){
    // geometry that will contain the vertices and colors of the digital grid
    // better if N is odd
    let geometryCells = new THREE.Geometry();
    let materialLines = new THREE.LineBasicMaterial({color: 0x0000ff});


    // return new THREE.LineSegments(geometryLine, materialLine);

    // loop over a set of digital points
    let j;
    for(j=0;j<N;j++){
        let x = j-(~~(N/2));
        geometryCells.vertices.push(new THREE.Vector3( x-0.5, min-0.5, 0));
        geometryCells.vertices.push(new THREE.Vector3( x-0.5, max+0.5, 0));
    }
    geometryCells.vertices.push(new THREE.Vector3( j-(~~(N/2))-0.5, min-0.5, 0));
    geometryCells.vertices.push(new THREE.Vector3( j-(~~(N/2))-0.5, max+0.5, 0));


    let i;
    for(i=0;i<N;i++){
        let y = i-(~~(N/2));
        geometryCells.vertices.push(new THREE.Vector3( min-0.5, y-0.5, 0));
        geometryCells.vertices.push(new THREE.Vector3( max+0.5, y-0.5, 0));
    }
    geometryCells.vertices.push(new THREE.Vector3(  min-0.5, i-(~~(N/2))-0.5, 0));
    geometryCells.vertices.push(new THREE.Vector3( max+0.5, i-(~~(N/2))-0.5, 0));


    return new THREE.LineSegments(geometryCells, materialLines);
}


// Rounding operation
// loop over all the points and round
function discretizeGeometry(geometryy){
    for (let i = 0; i < geometryy.vertices.length; i++) {
        geometryy.vertices[i].x = Math.round(geometryy.vertices[i].x);
        geometryy.vertices[i].y = Math.round(geometryy.vertices[i].y);
        geometryy.vertices[i].z = Math.round(geometryy.vertices[i].z);
    }
}

var setOfRemainders = function (reflectedVerticesGeometry){
    console.log(reflectedVerticesGeometry)
    // let geometryCells = new THREE.Geometry();
    // let materialLines = new THREE.LineBasicMaterial({color: 0x0000ff});
    let geometryRemainders = new THREE.Geometry();
    let materialRemainders = new THREE.LineBasicMaterial({color: 0xff0000});


    let setOfVectors=[];

    for (let i = 0; i < reflectedVerticesGeometry.geometry.vertices.length ; i++) {
        // let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x- Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), reflectedVerticesGeometry.geometry.vertices[i].y- Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );
        let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x, reflectedVerticesGeometry.geometry.vertices[i].y, 0 );
        // dir.normalize();
        let origin = new THREE.Vector3( Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );
        // let length = dir.length();

        // geometryRemainders.push(new THREE.ArrowHelper( dir, origin, length, 0xff0000 ));
        geometryRemainders.vertices.push(origin );
        geometryRemainders.vertices.push(dir );


        // reflectedVerticesGeometry.vertices[i].x = Math.round(geometryy.vertices[i].x);
        // reflectedVerticesGeometry.vertices[i].y = Math.round(geometryy.vertices[i].y);
        // reflectedVerticesGeometry.vertices[i].z = Math.round(geometryy.vertices[i].z);
    }

    return new THREE.LineSegments(geometryRemainders, materialRemainders);
}