import csv
import numpy as np
import matplotlib.pyplot as plot
from sklearn.metrics import r2_score
from sklearn.cluster import KMeans
from scipy import stats

# something wrong with the csv header, so list the names myself.
date = []
day = []
highTemp = []
lowTemp = []
precipitation = []
Brooklyn_Bridge = []
Manhattan_Bridge = []
Williamsburg_Bridge = []
Queensboro_Bridge = []
total = []

with open('NYC_Bicycle_Counts_2016_Corrected.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        date.append(row[0])
        day.append(row[1])
        highTemp.append(float(row[2]))
        lowTemp.append(float(row[3]))
        # because only a few day snows so not considering that, trace(near zero) is consider as 0.
        precipitation.append(float(row[4].replace(" (S)", "").replace("T", "0")))
        Brooklyn_Bridge.append(int(row[5].replace(',', '')))
        Manhattan_Bridge.append(int(row[6].replace(',', '')))
        Williamsburg_Bridge.append(int(row[7].replace(',', '')))
        Queensboro_Bridge.append(int(row[8].replace(',', '')))
        total.append(int(row[9].replace(',', '')))

    print('------------------prob1------------------')
    listBridge = ['Brooklyn_Bridge', 'Manhattan_Bridge', 'Williamsburg_Bridge', 'Queensboro_Bridge']
    for name in listBridge:
        bridge = eval(name)
        model = np.polyfit(bridge, total, 1)
        model = list(model)
        print("The coef for " + str(name) + " is " + str(model))
        bridgePre = []
        for i in bridge:
            bridgePre.append(i * model[0] + model[1])
        print('The r score for ' + name + ' ' + str(r2_score(total, bridgePre)))
        plot.plot(bridge, bridgePre, c="black", label='model')
        plot.xlabel(str(name) + ' bridge bicycles number')
        plot.scatter(bridge, total, c="grey", label='actual data')
        plot.ylabel('total bicycles number')
        plot.title(name)
        plot.legend()
        plot.show()

    print('------------------prob2------------------')

    avgTemp = []
    for z in range(len(highTemp)):
        avgTemp.append((highTemp[z] + lowTemp[z]) / 2)
    tempAvgCoef = np.polyfit(avgTemp, total, 1)

    print("The coef for average temperature model is " + str(tempAvgCoef[0]) + str(tempAvgCoef))

    # First method, not work.
    tempHCoef = np.polyfit(highTemp, total, 1)
    tempLCoef = np.polyfit(lowTemp, total, 1)

    tempAvgPre = []
    for temp in avgTemp:
        tempAvgPre.append(tempAvgCoef[0] * temp + 1)
    plot.plot(avgTemp, tempAvgPre, c='black', label='model')
    plot.scatter(avgTemp, total, c='grey', label='actual data')
    plot.xlabel('average temperature of the day')
    plot.ylabel('total bicyclists on the bridge')
    plot.title('average temperature vs. total bicyclists')
    plot.legend()
    plot.show()
    print('The r score for avg method is ' + str(r2_score(total, tempAvgPre)))

    # tempHPre = []
    # for tempH in highTemp:
    #     tempHPre.append(tempHCoef[0] * tempH + 1)
    #
    # tempLPre = []
    # for tempL in lowTemp:
    #     tempLPre.append(tempLCoef[0] * tempL + 1)
    #
    # plot.plot(highTemp, tempHPre)
    # plot.scatter(highTemp, total)
    # plot.show()
    #
    # plot.plot(lowTemp, tempLPre)
    # plot.scatter(lowTemp, total)
    # plot.show()


    # first method above.

    # second method below, better.
    totalHTemp = []
    totalLTemp = []
    for i in range(len(total)):
        totalHTemp.append(total[i] * highTemp[i])
        # print(highTemp[i])
        totalLTemp.append(total[i] * lowTemp[i])

    avgTotal = sum(total) / len(total)

    avgHTemp = sum(totalHTemp) / avgTotal / len(total)  # weighted average high temp
    avgLTemp = sum(totalLTemp) / avgTotal / len(total)  # weighted average low temp

    # print(avgTotal)
    print("The weighted average of highest temperature is " + str(avgHTemp))
    print("The weighted average of lowest temperature is " + str(avgLTemp))

    tempHbelow = []
    tempHabove = []
    tempLbelow = []
    tempLabove = []
    totalHbelow = []
    totalHabove = []
    totalLbelow = []
    totalLabove = []
    for hight in range(len(highTemp)):
        if highTemp[hight] < avgHTemp:
            tempHbelow.append(highTemp[hight])
            totalHbelow.append(total[hight])
        else:
            tempHabove.append(highTemp[hight])
            totalHabove.append(total[hight])

    for lowt in range(len(lowTemp)):
        if lowTemp[lowt] < avgLTemp:
            tempLbelow.append(lowTemp[lowt])
            totalLbelow.append(total[lowt])
        else:
            tempLabove.append(lowTemp[lowt])
            totalLabove.append(total[lowt])

    # print(tempHabove)
    # print(tempHbelow)
    # print(tempLabove)
    # print(tempLbelow)
    # print(totalHabove)

    listTemp = ['tempHabove', 'tempHbelow', 'tempLabove', 'tempLbelow']
    listTotal = ['totalHabove', 'totalHbelow', 'totalLabove', 'totalLbelow']
    for name in range(len(listTemp)):
        temp1 = eval(listTemp[name])
        total1 = eval(listTotal[name])
        model1 = np.polyfit(temp1, total1, 1)
        model1 = list(model1)
        print("The coef for " + str(listTemp[name]) + " is " + str(model1))
        tempPre = []
        for i in temp1:
            tempPre.append(i * model1[0] + model1[1])
        print('The r score for ' + str(listTemp[name]) + ' ' + str(r2_score(total1, tempPre)))
        plot.plot(temp1, tempPre, c="black", label='model')
        plot.xlabel(str(listTemp[name]) + ' temperature')
        plot.scatter(temp1, total1, c="grey", label='actual data')
        plot.ylabel('total bicycles number')
        plot.title(listTemp[name])
        plot.legend()
        plot.show()

    print('------------------prob3------------------')
    rain = []
    not_rain = []
    for i in range(len(precipitation)):
        if precipitation[i] == 0:
            not_rain.append(total[i])
        else:
            rain.append(total[i])

    n = len(not_rain)  # number of days not raining
    n2 = len(rain)  # number of days raining
    ave_rain = np.mean(rain)
    ave_not_rain = np.mean(not_rain)
    z_c = stats.norm.ppf(1 - (1 - 0.99) / 2)

    SE = np.sqrt(np.std(rain, ddof=1) ** 2 / n2)
    SE2 = np.sqrt(np.std(not_rain, ddof=1) ** 2 / n)

    low_rain = ave_rain - z_c * SE
    high_rain = ave_rain + z_c * SE
    low_not_rain = ave_not_rain - z_c * SE2
    high_not_rain = ave_not_rain + z_c * SE2

    print('Number of days not raining is {}'.format(n))
    print('Number of days raining is {}'.format(n2))
    print('Average Bike traffic for raining days is {}'.format(ave_rain))
    print('Average Bike traffic for no rainy days is {}'.format(ave_not_rain))
    print('99% confidence interval of bikes when raining is [{},{}]'.format(low_rain, high_rain))
    print('99% confidence interval of bikes when not raining is [{},{}]'.format(low_not_rain, high_not_rain))

    X = []
    for i in range(len(precipitation)):
        w = [precipitation[i], total[i]]
        X.append(w)
    X = np.array(X)

    kmeans = KMeans(n_clusters=2)
    kmeans.fit(X)
    ax = plot.gca()
    ax.scatter(X[:, 1], X[:, 0], c=kmeans.labels_, cmap='rainbow', label='model')
    centers = kmeans.cluster_centers_
    plot.scatter(centers[:, 1], centers[:, 0], marker='X')
    plot.legend()
    plot.title('Precipitation vs. Total bike traffic')
    plot.xlabel('Total bike traffic')
    plot.ylabel('Precipitation')
    plot.show()

    print('The centers of the two clusters are {} and {}'.format(centers[0], centers[1]))

    file.close()
