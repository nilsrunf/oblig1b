[a, b] = textread('res10.txt', '%f %f', 10);
x10 = linspace(0, 1, 10);
xlabel('x-verdier');
ylabel('f(x)-verdier');
figure(1);
plot(x10, 1-(1- exp(-10))*x10 - exp(-10*x10), '-r')%, a, b, '-b');

[a, b] = textread('res100.txt', '%f %f', 100);
x100 = linspace(0, 1, 100);
xlabel('x-verdier');
ylabel('f(x)-verdier');
figure(2);
plot(x100, 1-(1- exp(-10))*x100 - exp(-10*x100), '-r')%, a, b, '-b');

[a, b] = textread('res1000.txt', '%f %f', 1000);
x1000 = linspace(0, 1, 1000);
xlabel('x-verdier');
ylabel('f(x)-verdier');
figure(3);
plot(x1000, 1-(1- exp(-10))*x1000 - exp(-10*x1000), '-r')%, a, b, '-b');


