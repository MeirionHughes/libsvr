import { OnlineSVR, KernelType } from './index';

let svr = new OnlineSVR();

svr.clear();
svr.setC(3);
svr.setEpsilon(0.01);
svr.setKernel(KernelType.RBF_GAUSSIAN);
svr.setKernelParam(10);

let data = [1, 2, 3, 4, 5, 2, 1, 4, 5, 3, 1, 4, 3, 2, 7, 8]

let set = data.map((x1, i1) => {
  let i0 = Math.max(0, i1 - 1);
  let i2 = Math.min(data.length - 1, i1 + 1);
  let x0 = data[i0];
  let x2 = data[i2];
  return { x: [x0, x1], y: ((x2 > x1) ? 1 : -1) }
});

function predict(last, now) {
  let y = svr.predict([last, now]);

  let mag = Math.abs(y) >= 0.25;
  let act = (Math.sign(y) >= 1.0 && mag) ? "BUY" : "SELL";

  console.log(`${last}>${now} = ${act}`);
}

console.log("training...");

for (let [i1, { x, y }] of set.entries()) {
  svr.train(x, y);
}

console.log("predict");

for (let [i1, x1] of data.entries()) {
  let i0 = Math.max(0, i1 - 1);
  let i2 = Math.min(data.length - 1, i1 + 1);

  predict(data[i0], data[i1]);
}