%H1 Tilastollisten menetelmien jatkokurssi
%%
clearvars
close all
clc

%T1

%a
mu1 = 7.2;
sigma1 = 4.2;
sample1 = randn(1,20).*sigma1+mu1; %N(0,1)*sigma+myy = normeeraus

mu2 = 8.5;
sigma2 = 6.1;
sample2 = randn(1,20).*sigma2+mu2;

%b
mu_s1 = mean(sample1) % vektorin keskiarvo
mu_s2 = mean(sample2)
D = mu_s1-mu_s2 
var_s1 = var(sample1) % Laskee sarakkeen varianssin
var_s2 = var(sample2)
Q = var_s1/var_s2  

%c
D = zeros(1,50);
Q = zeros(1,50);

% D:n arvojen pit‰isi olla l‰hell‰ 1.3:a (8.5-7-2)
% Q:n arvojen pit‰isi olla l‰hell‰ 0.69:‰‰ (4.2/6.1) 

for i = 1:50
    mu1 = 7.2;
    sigma1 = 4.2;
    sample1 = randn(1,20).*sigma1+mu1;

    mu2 = 8.5;
    sigma2 = 6.1;
    sample2 = randn(1,20).*sigma2+mu2;

    mu_s1 = mean(sample1);
    mu_s2 = mean(sample2);
    D(i) = mu_s1-mu_s2;
    var_s1 = var(sample1);
    var_s2 = var(sample2);
    Q(i) = var_s1/var_s2;
    
end

figure(1)
histogram(D)
title('D 50')

figure(2)
histogram(Q)
title('Q 50')

D = zeros(1,1000);
Q = zeros(1,1000);

for i = 1:1000
    mu1 = 7.2;
    sigma1 = 4.2;
    sample1 = randn(1,20).*sigma1+mu1;

    mu2 = 8.5;
    sigma2 = 6.1;
    sample2 = randn(1,20).*sigma2+mu2;

    mu_s1 = mean(sample1);
    mu_s2 = mean(sample2);
    D(i) = mu_s1-mu_s2;
    var_s1 = var(sample1);
    var_s2 = var(sample2);
    Q(i) = var_s1/var_s2;
    
end

figure(3)
histogram(D)
title('D 1000')

figure(4)
histogram(Q)
title('Q 1000')

D = zeros(1,10000);
Q = zeros(1,10000);

for i = 1:10000
    mu1 = 7.2;
    sigma1 = 4.2;
    sample1 = randn(1,20).*sigma1+mu1;

    mu2 = 8.5;
    sigma2 = 6.1;
    sample2 = randn(1,20).*sigma2+mu2;

    mu_s1 = mean(sample1);
    mu_s2 = mean(sample2);
    D(i) = mu_s1-mu_s2;
    var_s1 = var(sample1);
    var_s2 = var(sample2);
    Q(i) = var_s1/var_s2;
    
end

figure(5)
histogram(D)
title('D 10000')

figure(6)
histogram(Q)
title('Q 10000')

%%
clearvars
close all
clc

%T2
load examgrades;
res = zeros(5,2);

%CDF = kertym‰funktio F(x)

for i = 1:5
    x = grades(:,i);
    test_cdf = [x,cdf('tlocationscale',x,75,10,1)];
    [h,p] = kstest(x,'CDF',test_cdf);
    res(i,1) = h;
    res(i,2)= p;
end 

res

% Matriisin ekassa sarakkeessa testitulos* ja tokassa p-arvo
% *Testitulos 1 = nollahypoteesi hyl‰t‰‰n 
%%
clearvars
close all
clc

%T3

load('RandD.mat')
data = RandD;

%a
parexp = expfit(data) % estimates the mean of an exponentially distributed sample
parwbl = wblfit(data) % Weibull parametres a & b 

%b
figure(1)
histogram(data,'Normalization','pdf') % Probability Density Function
hold on

figure(1)
y1 = pdf('Exponential',sort(data),parexp);
plot(sort(data),y1,'m')
title('Sorted')

figure(1)
y2 = pdf('Weibull',sort(data),parwbl(1),parwbl(2));
plot(sort(data),y2,'r')

legend('Data','Exponenetial','Weibull')

%c
% test the same data whether it can be coming from Weibull distribution
% create the CFD matrix
% the first column has the variable (outcome) values
% the second column has the CFD values for those variable values

test_cdfE = [data,cdf('Exponential',data,parexp)];
test_cdfW = [data,cdf('Weibull',data,parwbl(1),parwbl(2))];

[he,pe] = kstest(data,'CDF',test_cdfE); 
[hw,pw] = kstest(data,'CDF',test_cdfW);

[ad_he,ad_pe] = adtest(data,'Distribution','exp');
[ad_hw,ad_pw] = adtest(data,'Distribution','weibull');

he % nollahypoteesi hyv‰ksyt‰‰n
hw % nollahypoteesi hyv‰ksyt‰‰n
ad_he % nollahypoteesia ei hyv‰ksyt‰ (n‰in voi k‰yd‰, jos datapisteit‰ on v‰h‰n)
ad_hw % nollahypoteesi hyv‰ksyt‰‰n  

%d
% Empirical CDF of the data:
figure(2)
cdfplot(data)
hold on 

% CDF of the theoretical distribution 
plot (sort(data),sort(test_cdfE(:,2)),'m')
plot (sort(data),sort(test_cdfW(:,2)),'r')
legend('Data', 'Exponential', 'Weibull')
