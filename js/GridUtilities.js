
import * as THREE from './jslibs/three.module.js';

let forestGreen = new THREE.Color(0x009900);
let deepBlue = new THREE.Color(0x3774CB);
let deepRed = new THREE.Color(0x721606);
let red = new THREE.Color(0xff0000);

export var createDigitalPoint = function(x,y,z,color){
    // geometry that will contain the vertices and colors
    // the material will contain the thickness of the points
    let geometryPoint = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.1, vertexColors: true});

    geometryPoint.vertices.push(new THREE.Vector3(x,y,z));
    geometryPoint.colors.push(color);

    return new THREE.Points(geometryPoint,materialPoints);
}


export var createGrid = function(N){
    // geometry that will contain the vertices and colors of the digital grid
    // better if N is odd
    let geometryPoint = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.18, vertexColors: true});

    let idx = 0;
    // loop over a set of digital points
    for(let i=0;i<N;i++){
        for(let j=0;j<N;j++) {
            let x = j-(~~(N/2));
            let y = i-(~~(N/2));
            
            if(x==0 && y==1){
                console.log("coord 0,1 had idx = ",idx)
                console.log("N//2 = ",~~(N/2))
            }

            geometryPoint.vertices.push(new THREE.Vector3(x, y, 0));
            geometryPoint.colors.push(deepBlue);


            idx++
        }
    }
    return new THREE.Points(geometryPoint,materialPoints);
}

export var createCells = function(N,min,max){
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
export function discretizeGeometry(geometryy){
    for (let i = 0; i < geometryy.vertices.length; i++) {
        geometryy.vertices[i].x = Math.round(geometryy.vertices[i].x);
        geometryy.vertices[i].y = Math.round(geometryy.vertices[i].y);
        geometryy.vertices[i].z = Math.round(geometryy.vertices[i].z);
    }
}

export var setOfRemainders = function (reflectedVerticesGeometry,specifColor){

    let geometryRemainders = new THREE.Geometry();
    let materialRemainders = new THREE.LineBasicMaterial({color: specifColor});


    let setOfVectors=[];

    for (let i = 0; i < reflectedVerticesGeometry.geometry.vertices.length ; i++) {
        // let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x- Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), reflectedVerticesGeometry.geometry.vertices[i].y- Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );
        let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x, reflectedVerticesGeometry.geometry.vertices[i].y, 0 );

        let origin = new THREE.Vector3( Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );

        // if(Math.round(reflectedVerticesGeometry.geometry.vertices[i].x) == 1.0 && Math.round(reflectedVerticesGeometry.geometry.vertices[i].y) == 1.0){
        if(i == 29){
            console.log("i = "+i+" ; vecRemainder = ("+ (Math.round(reflectedVerticesGeometry.geometry.vertices[i].x) -reflectedVerticesGeometry.geometry.vertices[i].x)+", "+(Math.round(reflectedVerticesGeometry.geometry.vertices[i].y) -reflectedVerticesGeometry.geometry.vertices[i].y))
        }

        // geometryRemainders.push(new THREE.ArrowHelper( dir, origin, length, 0xff0000 ));
        geometryRemainders.vertices.push(origin );
        geometryRemainders.vertices.push(dir );


        // reflectedVerticesGeometry.vertices[i].x = Math.round(geometryy.vertices[i].x);
        // reflectedVerticesGeometry.vertices[i].y = Math.round(geometryy.vertices[i].y);
        // reflectedVerticesGeometry.vertices[i].z = Math.round(geometryy.vertices[i].z);
    }

    return new THREE.LineSegments(geometryRemainders, materialRemainders);
}


export var setOfRemaindersRestreined = function (reflectedVerticesGeometry,specifColor,a,b,N){
    // a,b are the coefficient of the direction vector

    let geometryRemainders = new THREE.Geometry();
    let materialRemainders = new THREE.LineBasicMaterial({color: specifColor});


    let idx_O = (~~(N/2)) + (~~(N/2))*N;

    console.log("idx_O = ",idx_O)


    let O = new THREE.Vector3(0.0,0.0,0.0);

    let setOfVectors=[];

    for (let yy = -a; yy < (b+1) ; yy++) {
        for (let xx = (-a)-1; xx < b ; xx++) {
            // for (let xx = 1-b; xx < (-a) ; xx++) {

            console.log("xx = ",xx," ; yy = ",yy)

            let i = idx_O + xx + N*yy;

            let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x- Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), reflectedVerticesGeometry.geometry.vertices[i].y- Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );
            // let dir = new THREE.Vector3(reflectedVerticesGeometry.geometry.vertices[i].x, reflectedVerticesGeometry.geometry.vertices[i].y, 0 );
            // let origin = new THREE.Vector3( Math.round(reflectedVerticesGeometry.geometry.vertices[i].x), Math.round(reflectedVerticesGeometry.geometry.vertices[i].y), 0 );
            
            console.log("vector remainder = (", dir.x-O.x,", ", dir.y-O.y,")");
            
            // geometryRemainders.vertices.push(origin );
            // geometryRemainders.vertices.push(dir );
            geometryRemainders.vertices.push(O );
            geometryRemainders.vertices.push(dir );
    

        // reflect


        }
        // geometryRemainders.vertices.push(origin );
        // geometryRemainders.vertices.push(dir );


    }

    return new THREE.LineSegments(geometryRemainders, materialRemainders);
}