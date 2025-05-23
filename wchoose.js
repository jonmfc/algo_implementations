```javascript
/* Chooses a random element from a list of choices, with a probability proportional to the provided weights.
By: Jonathan Mitelman */
function weightedRandomChoice(choices, weights) {
  if (!Array.isArray(choices) || !Array.isArray(weights)) {
    return null;
  }

  if (choices.length !== weights.length) {
    return null;
  }

  if (weights.some(w => w < 0)) {
    return null;
  }

  const totalWeight = weights.reduce((sum, w) => sum + w, 0);
  if (totalWeight === 0) {
    return null;
  }

  const normalizedWeights = weights.map(w => w / totalWeight);

  const cumulativeWeights = [0.0];
  for (const weight of normalizedWeights) {
    cumulativeWeights.push(cumulativeWeights[cumulativeWeights.length - 1] + weight);
  }

  const randomNumber = Math.random();

  for (let i = 0; i < choices.length; i++) {
    if (randomNumber >= cumulativeWeights[i] && randomNumber < cumulativeWeights[i + 1]) {
      return choices[i];
    }
  }

  return null;
}

function main() {
  const items = ["A", "B", "C", "D"];
  const itemWeights = [0.5, 0.2, 0.2, 0.1];

  const numTrials = 10000;
  const results = {};
  for (const item of items) {
    results[item] = 0;
  }

  for (let i = 0; i < numTrials; i++) {
    const chosenItem = weightedRandomChoice(items, itemWeights);
    if (chosenItem) {
      results[chosenItem]++;
    }
  }

  console.log("Simulated results after", numTrials, "trials:");
  for (const item in results) {
    const count = results[item];
    const probability = count / numTrials;
    console.log(`  ${item}: ${count} (Probability: ${probability.toFixed(3)})`);
  }

  const result1 = weightedRandomChoice(["X", "Y"], [1, 2, 3]);
  console.log(`Example of incorrect input (different lengths): ${result1}`);

  const result2 = weightedRandomChoice(["Z", "Q"], [-1, 2]);
  console.log(`Example of incorrect input (negative weight): ${result2}`);
}

main();
```