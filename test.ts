import {OnlineSVR} from './index';

console.log(OnlineSVR);


let svr = new OnlineSVR(10);

console.log(svr.train([1], 1));
console.log(svr.train([-1], -1));