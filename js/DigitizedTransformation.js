import * as THREE from './jslibs/three.module.js';

let forestGreen = new THREE.Color(0x009900);
let deepBlue = new THREE.Color(0x3774CB);
let deepRed = new THREE.Color(0x721606);
let red = new THREE.Color(0xff0000);

// just to try
export var reflectPoint = function (points_i,normalVector) {
    // reflect a set of points given by the "geometry" points_i with respect to the normal vector given by normalVector;
    // The normal vector is not necessarily a unit normal vector

    let normNormalVector = Math.sqrt(normalVector[0]*normalVector[0]+normalVector[1]*normalVector[1]+normalVector[2]*normalVector[2]+normalVector[3]*normalVector[3]);

    let unitNormVector = [normNormalVector[0]/normNormalVector,normNormalVector[1]/normNormalVector,normNormalVector[2]/normNormalVector,normNormalVector[3]/normNormalVector];

    let unitDirectionVector = [unitNormVector[1],-unitNormVector[0],unitNormVector[2],unitNormVector[3]]

    let geometryReflectedPoints = new THREE.Geometry();
    geometryReflectedPoints.vertices = points_i.vertices.clone();
    geometryReflectedPoints.colors = points_i.colors.clone();


    let ReflectionTransformation = new THREE.Matrix4();
    ReflectionTransformation.elements = [ 1-(2*unitDirectionVector[0]*unitDirectionVector[0]), -2*unitDirectionVector[0]*unitDirectionVector[1], -2*unitDirectionVector[0]*unitDirectionVector[2], -2*unitDirectionVector[0]*unitDirectionVector[3],
        -2*unitDirectionVector[0]*unitDirectionVector[1], 1-2*(unitDirectionVector[1]*unitDirectionVector[1]), -2*unitDirectionVector[1]*unitDirectionVector[2], -2*unitDirectionVector[1]*unitDirectionVector[3],
        -2*unitDirectionVector[0]*unitDirectionVector[2], -2*unitDirectionVector[1]*unitDirectionVector[2], 1-2*(unitDirectionVector[2]*unitDirectionVector[2]), -2*unitDirectionVector[2]*unitDirectionVector[3],
        0.0, 0.0, 0.0, 1.0 ];

    geometryReflectedPoints.applyMatrix4(ReflectionTransformation);

    return geometryReflectedPoints;
}

export var digitalReflectionOfPoints = function (points_i,normalVector1) {
    let normNormalVector1 = Math.sqrt(normalVector1[0]*normalVector1[0]+normalVector1[1]*normalVector1[1]+normalVector1[2]*normalVector1[2]+normalVector1[3]*normalVector1[3]);
    let unitNormVector1 = [normalVector1[0]/normNormalVector1,normalVector1[1]/normNormalVector1,normalVector1[2]/normNormalVector1,normalVector1[3]/normNormalVector1];
    let unitDirectionVector1 = [unitNormVector1[1],-unitNormVector1[0],unitNormVector1[2],unitNormVector1[3]]

    let geometryReflectedPoints1 = new THREE.Geometry();
    geometryReflectedPoints1.vertices = _.cloneDeep(points_i.geometry.vertices);//JSON.parse(JSON.stringify(points_i.geometry.vertices));
    geometryReflectedPoints1.colors = _.cloneDeep(points_i.geometry.colors);


    let ReflectionTransformation1 = new THREE.Matrix4();
    ReflectionTransformation1.elements = [ 1-(2*unitDirectionVector1[0]*unitDirectionVector1[0]), -2*unitDirectionVector1[0]*unitDirectionVector1[1], -2*unitDirectionVector1[0]*unitDirectionVector1[2], -2*unitDirectionVector1[0]*unitDirectionVector1[3],
        -2*unitDirectionVector1[0]*unitDirectionVector1[1], 1-2*(unitDirectionVector1[1]*unitDirectionVector1[1]), -2*unitDirectionVector1[1]*unitDirectionVector1[2], -2*unitDirectionVector1[1]*unitDirectionVector1[3],
        -2*unitDirectionVector1[0]*unitDirectionVector1[2], -2*unitDirectionVector1[1]*unitDirectionVector1[2], 1-2*(unitDirectionVector1[2]*unitDirectionVector1[2]), -2*unitDirectionVector1[2]*unitDirectionVector1[3],
        0.0, 0.0, 0.0, 1.0 ];

    geometryReflectedPoints1.applyMatrix4(ReflectionTransformation1);

    return new THREE.Points(geometryReflectedPoints1,points_i.material);
}


export var digitalRotationFromReflections = function (points_i,normalVector1,normalVector2) {
    // reflect a set of points given by the "geometry" points_i with respect to the normal vector given by normalVector;
    // The normal vector is not necessarily a unit normal vector

    let normNormalVector1 = Math.sqrt(normalVector1[0]*normalVector1[0]+normalVector1[1]*normalVector1[1]+normalVector1[2]*normalVector1[2]+normalVector1[3]*normalVector1[3]);
    let unitNormVector1 = [normalVector1[0]/normNormalVector1,normalVector1[1]/normNormalVector1,normalVector1[2]/normNormalVector1,normalVector1[3]/normNormalVector1];

    let normNormalVector2 = Math.sqrt(normalVector2[0]*normalVector2[0]+normalVector2[1]*normalVector2[1]+normalVector2[2]*normalVector2[2]+normalVector2[3]*normalVector2[3]);
    let unitNormVector2 = [normalVector2[0]/normNormalVector2,normalVector2[1]/normNormalVector2,normalVector2[2]/normNormalVector2,normalVector2[3]/normNormalVector2];

    let unitDirectionVector1 = [unitNormVector1[1],-unitNormVector1[0],unitNormVector1[2],unitNormVector1[3]]
    let unitDirectionVector2 = [unitNormVector2[1],-unitNormVector2[0],unitNormVector2[2],unitNormVector2[3]]

    console.log("unit dir vector 1 = ",unitDirectionVector1);

    let geometryReflectedPoints1 = new THREE.Geometry();
    geometryReflectedPoints1.vertices = _.cloneDeep(points_i.geometry.vertices);//JSON.parse(JSON.stringify(points_i.geometry.vertices));
    geometryReflectedPoints1.colors = _.cloneDeep(points_i.geometry.colors);


    let ReflectionTransformation1 = new THREE.Matrix4();
    ReflectionTransformation1.elements = [ 1-(2*unitDirectionVector1[0]*unitDirectionVector1[0]), -2*unitDirectionVector1[0]*unitDirectionVector1[1], -2*unitDirectionVector1[0]*unitDirectionVector1[2], -2*unitDirectionVector1[0]*unitDirectionVector1[3],
        -2*unitDirectionVector1[0]*unitDirectionVector1[1], 1-2*(unitDirectionVector1[1]*unitDirectionVector1[1]), -2*unitDirectionVector1[1]*unitDirectionVector1[2], -2*unitDirectionVector1[1]*unitDirectionVector1[3],
        -2*unitDirectionVector1[0]*unitDirectionVector1[2], -2*unitDirectionVector1[1]*unitDirectionVector1[2], 1-2*(unitDirectionVector1[2]*unitDirectionVector1[2]), -2*unitDirectionVector1[2]*unitDirectionVector1[3],
        0.0, 0.0, 0.0, 1.0 ];

    let ReflectionTransformation2 = new THREE.Matrix4();
    ReflectionTransformation2.elements = [ 1-(2*unitDirectionVector2[0]*unitDirectionVector2[0]), -2*unitDirectionVector2[0]*unitDirectionVector2[1], -2*unitDirectionVector2[0]*unitDirectionVector2[2], -2*unitDirectionVector2[0]*unitDirectionVector2[3],
        -2*unitDirectionVector2[0]*unitDirectionVector2[1], 1-2*(unitDirectionVector2[1]*unitDirectionVector2[1]), -2*unitDirectionVector2[1]*unitDirectionVector2[2], -2*unitDirectionVector2[1]*unitDirectionVector2[3],
        -2*unitDirectionVector2[0]*unitDirectionVector2[2], -2*unitDirectionVector2[1]*unitDirectionVector2[2], 1-2*(unitDirectionVector2[2]*unitDirectionVector2[2]), -2*unitDirectionVector2[2]*unitDirectionVector2[3],
        0.0, 0.0, 0.0, 1.0 ];

    // apply the first reflection transformation
    geometryReflectedPoints1.applyMatrix4(ReflectionTransformation1);
    console.log("first reflected points = ",geometryReflectedPoints1.vertices);
    // discretization of the first set of reflected points
    discretizeGeometry(geometryReflectedPoints1);


    // apply the first reflection transformation
    // Second reflection
    let geometryReflectedPoints2 = new THREE.Geometry();
    geometryReflectedPoints2.vertices = _.cloneDeep(geometryReflectedPoints1.vertices);//JSON.parse(JSON.stringify(points_i.geometry.vertices));
    geometryReflectedPoints2.colors = _.cloneDeep(geometryReflectedPoints1.colors);

    // apply the second reflection transformation
    geometryReflectedPoints2.applyMatrix4(ReflectionTransformation2);
    discretizeGeometry(geometryReflectedPoints2);

    return new THREE.Points(geometryReflectedPoints2,points_i.material);
}




// from a known resolution named kmax, compute the set of points that make bijective a digital reflection
// returns a geometry
export var  pointsMakingReflectionBijective = function (Kmax) {
    let pointsBijectiveReflection = new THREE.Geometry();
    let materialPoints = new THREE.PointsMaterial({color:0xffffff, size: 0.08, vertexColors: true});


    for (let k = 0; k < Kmax; k++) {
        let currentBijetivePoint_0_45 = new THREE.Vector3((k + 1.0) / (Math.sqrt(2.0 * k * k + 2.0 * k + 1.0)),
                                                     (k)       / (Math.sqrt(2.0 * k * k + 2.0 * k + 1.0)),
                                                      0.0);
        let currentBijetivePoint_45_90 = new THREE.Vector3((k ) / (Math.sqrt(2.0 * k * k + 2.0 * k + 1.0)),
            (k+1)       / (Math.sqrt(2.0 * k * k + 2.0 * k + 1.0)),
            0.0);

        let currentBijetivePoint_0_45_b = new THREE.Vector3((2*k + 1.0) / (Math.sqrt(4.0 * k * k + 4.0 * k + 2.0)),
                                                     (1)       / (Math.sqrt(4.0 * k * k + 4.0 * k + 2.0)),
                                                      0.0);
        let currentBijetivePoint_45_90_b = new THREE.Vector3((1 ) / (Math.sqrt(4.0 * k * k + 4.0 * k + 2.0)),
            (2*k+1)       / (Math.sqrt(4.0 * k * k + 4.0 * k + 2.0)),
            0.0);


        let currentBijetivePoint_0_45_c = new THREE.Vector3((2*k + 1.0) / (Math.sqrt(8.0 * k * k + 4.0 * k + 1.0)),
                                                     (2*k)       / (Math.sqrt(8.0 * k * k + 4.0 * k + 1.0)),
                                                      0.0);
        let currentBijetivePoint_45_90_c = new THREE.Vector3((2*k ) / (Math.sqrt(8.0 * k * k + 4.0 * k + 1.0)),
            (2*k+1.0)       / (Math.sqrt(8.0 * k * k + 4.0 * k + 1.0)),
            0.0);



        pointsBijectiveReflection.vertices.push(currentBijetivePoint_0_45);
        pointsBijectiveReflection.vertices.push(currentBijetivePoint_45_90);
        pointsBijectiveReflection.vertices.push(currentBijetivePoint_0_45_b);
        pointsBijectiveReflection.vertices.push(currentBijetivePoint_45_90_b);
        pointsBijectiveReflection.vertices.push(currentBijetivePoint_0_45_c);
        pointsBijectiveReflection.vertices.push(currentBijetivePoint_45_90_c);
        pointsBijectiveReflection.colors.push(forestGreen);
        pointsBijectiveReflection.colors.push(forestGreen);
        pointsBijectiveReflection.colors.push(forestGreen);
        pointsBijectiveReflection.colors.push(forestGreen);
        pointsBijectiveReflection.colors.push(forestGreen);
        pointsBijectiveReflection.colors.push(forestGreen);

    }
    return new THREE.Points(pointsBijectiveReflection,materialPoints);
};








let shearPoints_chs = function (points_i,theta) {
    // apply a digital shear transformation to a set of points given inside the geometry of points_i

    let ap = Math.floor(omega*Math.cos(theta));
    let bp = Math.floor(omega*Math.sin(theta));
    let cp = Math.floor(bp/2.0);
    digitalLine = [-ap,bp,cp];


    let a = digitalLine[0];
    let b = digitalLine[1];
    let c = digitalLine[2];


    let geometryReflectedPoints = new THREE.Geometry();
    geometryReflectedPoints.vertices = _.cloneDeep(points_i.geometry.vertices);//JSON.parse(JSON.stringify(points_i.geometry.vertices));
    geometryReflectedPoints.colors = _.cloneDeep(points_i.geometry.colors);
    console.log(geometryReflectedPoints.colors)

    for(let i=0;i<geometryReflectedPoints.vertices.length;i++){
        let shearCoefficient = ((a*(geometryReflectedPoints.vertices[i].y)+c)/b);
        geometryReflectedPoints.vertices[i].x = geometryReflectedPoints.vertices[i].x + shearCoefficient;
    }

    return new THREE.Points(geometryReflectedPoints,points_i.material);
}

let shearPoints_vqs = function (points_i,theta, omega) {
    // apply a digital shear transformation to a set of points given inside the geometry of points_i

    let a = Math.floor(omega*Math.sin(theta));
    let cp = Math.floor(omega/2.0);
    let b = omega;
    let c = cp;

    let geometryReflectedPoints = new THREE.Geometry();
    geometryReflectedPoints.vertices = _.cloneDeep(points_i.geometry.vertices);
    geometryReflectedPoints.colors = _.cloneDeep(points_i.geometry.colors);

    for(let i=0;i<geometryReflectedPoints.vertices.length;i++){
        let shearCoefficient = Math.floor((a*(geometryReflectedPoints.vertices[i].x)+c)/b);
        geometryReflectedPoints.vertices[i].y = geometryReflectedPoints.vertices[i].y + shearCoefficient;
    }

    return new THREE.Points(geometryReflectedPoints,points_i.material);
}


export var digitalRotationFromShear = function (points_i,alph) {
    // compute the digitized rotation from the quasi shear algorithm

    let first_hqs = shearPoints_hqs(geometry_Grid,theta,omega);
    let second_vqs = shearPoints_vqs(first_hqs,theta,omega);//first_hqs
    let third_vqs = shearPoints_hqs(second_vqs,theta,omega);
  

    return third_vqs;
}