SIXT33N Robotic Car
by Nathan Le and Haggai Kaunda

This is a self driving car that moves on specific voice command inputs. My partner and I implemented this project for our Devices and Design class, EE16B. It was a semester long project that implemented many of the concepts we learned in class. We created own circuit design, assembled all the hardware for the robotic car, and implemented the code on the TI Launchpad that would take real-time data from the motors and execute our code based on those changes. Throughout the process, we got to experiment with the quality and design of our various signal filters and implement machine learning algorithms. At the programming level, we monitored our data using IPython notebook to implement PCA and k-means to cluster and approximate the accuracy of out input words. Based on the accuracy of our words, we proceeded to implement that algorithm in our TI-Launchpad to test our car's live response. Through a series of several integration test, we optimized the efficiency of our car, by experimenting with the signal filters of our circuit design and by pruning outliers from our K-means clustering data to increase voice recognition accuracy.


Circuit:

Final Design, Front End Circuit, and Frequency and Gain Response:
The front end circuit was feed by the output to the mic board circuit and consisted of three main stages, a 2nd order low pass filter with a cut off frequency of 1.5KHz, a non-inverting amplifier with a gain of 10, and a buffer stage. A signal from the the mic was channeled through these three stages before being feed into the Launchpad, as described below. 

The first stop for a signal coming into the front end circuit from the mic board was the 2nd order low pass filter where the it was filtered for any low frequency signals to clean it up from noisy signals. A second order filter was used to take advantage of it’s steep slop and thus increasing the quality of the signal that goes through this stage. From here, the signals was then feed into a non-inverting amplifier stage that was grounded at an offset of 1.6V relative to 0, so as to keep the signal centered about this voltage. The amplifier saved to ramp up the voltage from of the signal before being sent to launch pad to ensure that it wasn’t too low and thus not be detected. On wards, the signal was then feed into the buffer stage that served to decouple the current flowing in from the previous stages. Finally the signal was sent to the Launch pad for further processing and classification. 


PCA Classification:

Commands:
Word 1: okay
Word 2: amor
Word 3: jazz
Word 4: hilfinger

We specifically chose these words as they had distinct waveforms to their pronunciations. Also, we chose these words because the timbre of our voices and the attack of our speech made it easier to group our clusters. Words with the same amount of syllables and similar vowel sounds tended to have non-differentiable clusters. Furthermore, what helped us choose our words was looking at the waveform and seeing where the peaks/emphasis in the waves were. The more the waveforms matched each other made the classifying much harder. Some of the words that did not work were “cortana”,  “delta” , and “epsilon”. This issue had to do with the length of the word and the attack of the syllables. For “delta” and “epsilon” , the attack of the first syllable is so similar that classifying these words became nearly impossible.


Processing:
We mad our classification much more robust by shifting the clusters, changing our data set for particular words, and practicing word pronunciation. We practiced how we would pronounce our words and time it according the 2 second sample size. This helped guarantee that the data would have similar waveform. When we settled upon words that had distinct enough clusters, we manually took the centroid coordinates given by our PCA Classification and shifted them to an arbitrary location that covered a greater majority of our data cluster, making our centroids more accurate. From there, we cleaned our data set after making sure we had enough samples to remove any data that was an outlier and would always lie outside our K-means threshold.



Controls:

Open Loop Model:
In the open Loop Model, the idea is to make the system reach a desired state by applying a predefined input sequence, that is calculated to bring the system to the desired state, assuming no disturbances or changes in the system once the input is applied. 

Closed Loop Model:
As for open Loop, closed loop also tries to take a given system to a desired state. The only difference is that open loop takes into account disturbances that may arise as the system evolves to reach the required target by applying a control feed back mechanism to the input sequence that is continuous feed to the system. The resulting effect is a more robust mechanism that is stabilizes it self in the face of disturbances to reach the desired target state. This is why a closed Loop Mode is needed or desired over an open loop, we cannot simply rely on a computed input sequence and hope for the best because where disturbances arise, open loop fails. 

Choosing Controller Values:
Because we modeled a continuous time system as a discrete time system, we also needed to apply a discrete time control mechanism. As such the goal and purpose of choosing our k values was hanged on the proven fact that a discrete time system converges to the desired state for k values within the unit circle. Following that we set on to try and design out system so that it converged to the desired velocity in a reasonable amount of time. We didn’t try to make it converge immediately as this would require and infinite amount of power supply. After experimenting with different k-values we finally settled on setting kl to -0.2 and kr to 0.1 to achieve the desired behavior. The end result was a stable system that seemed to converge almost immediately to the human eye. 


General:

The most enjoyable thing we enjoyed in this project was seeing the connection between hardware and software, and seeing their reliance on one another to implement many of the devices we have today. More fundamentally, we learned the step by process of debugging our circuit. We stumbled many times in lab, trying to figure out where the error in our circuit was at. This involved checking our circuit schematic, and probing our output and inputs at all portions in our circuit. What happened many times in lab was that we did not default to probing our circuit to determine the error, before asking a TA or Lab assistant for help. Other times though, we would spend about an hour checking on schematic and circuit for loose connections, only to find that we had broken hardware in our circuit or in our probing tools.

For the final demonstration, we noticed after all the controls testing that the hardware in our motors began jamming. This was an issue because sometimes, we would give our car a command and then have to give it an initial push to unstick the jamming the wheels. We took on TA’s recommendation to give our wheels a greater initial velocity, but the wheels a few times during testing would still jam. Also, another issue we realize late into the project, was that by not locking the front wheel in place correctly, no matter how accurate our control’s code was, the car would move in the wrong direction. We fixed this using a lot of tape to secure the wheel, but it if we had a fixed front wheel to begin with, we would have a better idea if our Energia code was classifying incorrectly or not.
