#Lecture 5: Forecasting

rm(list=ls())

library(datasets)
library(ggplot2)
library(dplyr)
library(corrplot)

install.packages("tsoutliers")
library(tsoutliers)

#6 Properties of Linear Regression (OLS):

#Example 1

icecream = read.csv("IceCream.csv", header = TRUE, sep = ";")

#1. The explanatory variables are not linearly dependent
# Ok

#Construct a linear regression model lm()
model1 = lm(Sales_Weekly~Avg_Temp, data = icecream)

summary(model1)

ggplot(icecream,aes(x=Avg_Temp, y=Sales_Weekly))+
  geom_point()+
  geom_line(aes(x=Avg_Temp, y = fitted.values(model1)), col="red")

#2. Residuals (=errors) have zero mean
mean(residuals(model1))

#3. The variance of the residuals is constant (and finite)
#   -> Homoskedasticity

#&

#4. The residuals are linearly independent of one another

plot(residuals(model1), type="p", col="blue", ylim=c(-10,10),pch=16,
     ylab = "Residuals", main="Residuals over time")
abline(a=3*sd(residuals(model1)),b=0,col="red",lty=2)
abline(a=-3*sd(residuals(model1)),b=0,col="red",lty=2)
abline(a=0,b=0,col="black", lty=2)

#5. There is no relationship between the residuals and each of the explanatory
#   variables
cor(residuals(model1),icecream$Avg_Temp)

#6. The residuals are normally distributed
JarqueBera.test(residuals(model1))

#Example 2

icecream = read.csv("IceCream_2.csv", header=TRUE, sep=";")

str(mtcars)
depvar = mtcars$mpg
exvars = mtcars[,2:11]

corrplot(cor(exvars),"number")

cormat = abs(cor(exvars))
diag(cormat) = 0

#1. The explanatory variables are not linearly dependent

while(max(cormat)>=0.8){
  # Find explanatory variable with highest absolute correlation
  maxvar = which(cormat==max(cormat), arr.ind = TRUE)
  
  # Select variable with the highest average correlation
  maxavg = which.max(rowMeans(cormat[maxvar[,1],]))
  
  # FYI
  print(rownames(maxvar)[maxvar[,1]==maxvar[maxavg,1]])
  
  # Removal
  exvars = exvars[,-maxvar[maxavg,1]]
  cormat = cormat[-maxvar[maxavg,1],-maxvar[maxavg,1]]
}

# Build the model
my_data = cbind('mpg'=depvar, exvars)

linRegModel = lm(mpg~hp+drat+wt+qsec+vs+am+gear+carb, data = my_data)
summary(linRegModel)

linRegModel = lm(mpg~hp+drat+wt+qsec+am+gear+carb, data = my_data)
summary(linRegModel)

linRegModel = lm(mpg~hp+drat+wt+qsec+am+carb, data = my_data)
summary(linRegModel)

linRegModel = lm(mpg~hp+wt+qsec+am+carb, data = my_data)
summary(linRegModel)

linRegModel = lm(mpg~wt+qsec+am, data = my_data)
summary(linRegModel)