


var reflectPoint = function (points_i,normalVector) {
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

var digitalReflectionOfPoints = function (points_i,normalVector1) {
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


var digitalRotationFromReflections = function (points_i,normalVector1,normalVector2) {
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