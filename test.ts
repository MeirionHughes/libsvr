import { OnlineSVR, KernelType } from './index';

let svr = new OnlineSVR();

svr.clear();
svr.setC(30);
svr.setEpsilon(0.01);
svr.setKernel(KernelType.RBF);
svr.setKernelParam(30);

let set = [
  {x:[-1, -1], y: -1},
  {x:[1, -1], y: 1},
  {x:[-1, 1], y: 1},
  {x:[1, 1], y: -1}
]

for(let {x, y} of set){
  svr.train(x, y);
}

for(let {x, y} of set){
  let $class = Math.sign(svr.predict(x));
  console.log($class == Math.sign(y));
}

console.log("supports", svr.getSupportSetElementsNumber());
console.log("errors", svr.getErrorSetElementsNumber());
console.log("remaining", svr.getRemainingSetElementsNumber());

