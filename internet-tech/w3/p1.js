let bill = [
    { name: "apple", count: 5, price: 70 },
    { name: "orange", count: 10, price: 90 },
    { name: "grapes", count: 165, price: 62 },
    { name: "radish", count: 3, price: 74 },
    { name: "melon", count: 12, price: 33 },
    { name: "mango", count: 4, price: 77 },
    { name: "lichi", count: 77, price: 445 },
];

let r = 0;
bill.forEach(e => {
    r += e.count * e.price;
});

let result = {
    bill: bill,
    result: r
};

console.log(JSON.stringify(result));

console.log(Date.now());
