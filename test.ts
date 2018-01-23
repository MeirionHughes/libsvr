import { OnlineSVR } from './index';

let svr = new OnlineSVR();

let data = [1, 2, 3, 4, 5, 2, 1, 4, 5, 3, 1, 4, 3, 2, 7, 8]

let set = data.map((x1, i1) => {
  let i0 = Math.max(0, i1 - 1);
  let i2 = Math.min(data.length - 1, i1 + 1);
  let x0 = data[i0];
  let x2 = data[i2];
  return { x: [x0, x1], y: ((x2 > x1) ? 1 : -1) }
});

for (let { x, y } of set) {
  svr.train(x, y);
}

function predict(last, now) {
  let y = svr.predict([last, now]);

  let mag = Math.abs(y) >= 0.25;
  let act = Math.sign(y) >= 1.0 && mag ? "BUY" : "SELL";

  console.log(`${last}>${now} = ${act}`);
}

for(let [i1, x1] of data.entries()){
  let i0 = Math.max(0, i1 - 1);
  let i2 = Math.min(data.length - 1, i1 + 1);

  predict(data[i0], data[i1]);
}