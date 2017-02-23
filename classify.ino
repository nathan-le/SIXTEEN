
/* integration.ino
** Processing Integration sketch for SIXT33N Speech version
** 
** EE16B Spring 2016
** Emily Naviasky & Nathaniel Mailoa
**
*/

//define constants
#define MIC_INPUT P6_1
#define SIZE 2752
#define SIZE_AFTER_FILTER 172


/*---------------*/
/* CODE BLOCK A1 */
/*---------------*/

// Enveloping and K-means constants
#define SNIPPET_SIZE 120 // YOUR CODE HERE 
#define PRELENGTH 10 // YOUR CODE HERE 
#define THRESHOLD 0.5// YOUR CODE HERE 

#define KMEANS_THRESHOLD 0.1// YOUR CODE HERE 
#define LOUDNESS_THRESHOLD 700// YOUR CODE HERE 

/*----------------------*/
/* END OF CODE BLOCK A1 */
/*----------------------*/

/*---------------*/
/* CODE BLOCK A2 */
/*---------------*/

//define arrays
float pca_vec1[SNIPPET_SIZE] = {-0.00527439816451, -0.00328211397292, -0.00459847724757, -0.00629147958423, -0.00387487392147, -0.00531737436366, -0.00464408482736, -0.00298977071513, 0.0139474040821, 0.0301363050059, 0.0840266860464, 0.0597956083842, 0.0957966378082, 0.0875335130182, 0.101969848243, 0.106678851232, 0.103219026927, 0.0997500141909, 0.0991396607609, 0.0825296586493, 0.0772993549842, 0.0741340312293, 0.0680933902307, 0.0686238187299, 0.0659566239808, 0.0696055521467, 0.071485433588, 0.0684948370586, 0.073268565651, 0.075258263611, 0.0634166744366, 0.073071294433, 0.0616076385362, 0.0759916663093, 0.0645354755444, 0.0718106441735, 0.0663471190009, 0.0697285812445, 0.0727297421794, 0.0692587822893, 0.0762487002935, 0.0851367025704, 0.101008260205, 0.106415718098, 0.101191979246, 0.113959918463, 0.102520668522, 0.118208818972, 0.110345257229, 0.111953004518, 0.119474557649, 0.104963211761, 0.115618086307, 0.102783466611, 0.105641412364, 0.106553190273, 0.0889474655665, 0.0989538728003, 0.0812978753846, 0.0839169935246, 0.0722142750744, 0.0752071410824, 0.0627713874124, 0.0627480446284, 0.0521714533343, 0.0547608160532, 0.0446255294138, 0.0314640220659, 0.0361560114984, 0.0152379794883, 0.0152217587347, 0.002366682725, 0.0129490720538, -0.0128264912205, -0.00113054065557, -0.0215226631007, -0.0225764219076, -0.0460527468389, -0.0458416283956, -0.0544118330138, -0.0691785677901, -0.0710791010129, -0.0800327603448, -0.0932333895049, -0.0916784482694, -0.0894944177629, -0.100044890213, -0.104902588832, -0.0991791243429, -0.117338967306, -0.118151219791, -0.114207263448, -0.112041932982, -0.124375313322, -0.119742911291, -0.119911050983, -0.125970211819, -0.119856683132, -0.123914806793, -0.135479933184, -0.127166310287, -0.12929231909, -0.137691975865, -0.135917600053, -0.133420763081, -0.135255962332, -0.139290298775, -0.134081832239, -0.140934782319, -0.12805420294, -0.136673207495, -0.144585129374, -0.131533395632, -0.128799520863, -0.127932206729, -0.117147071842, -0.121418932307, -0.114364756303, -0.102110618429, -0.10215467162}; // YOUR CODE HERE
float pca_vec2[SNIPPET_SIZE] = {-0.00598739187966, -0.00848884187409, -0.00856328972059, -0.0101599332125, -0.00662868501398, -0.00613576656792, -0.0144063397011, -0.0110385365319, -0.000506973983059, 0.03214678134, 0.11915856581, 0.0264808865354, 0.110084738064, 0.0293227576299, 0.0824706028494, 0.0395139244317, 0.0344214654637, 0.0147168131005, -0.0419015116979, -0.0574821900676, -0.100461681966, -0.12600849967, -0.173955288768, -0.172192291652, -0.19181262202, -0.189108161704, -0.195164278978, -0.200427485485, -0.193830217707, -0.201634679167, -0.186332146153, -0.193586262531, -0.16944283888, -0.190188799597, -0.158027714448, -0.178035887402, -0.153189287097, -0.150668629055, -0.132722511161, -0.133893571968, -0.103567632646, -0.0681083612442, -0.0123906677169, 0.00640257722691, 0.0135834010996, 0.0539471258969, 0.0200203129885, 0.0852430963641, 0.0623325557239, 0.0823067716838, 0.0989769931122, 0.0876699837816, 0.116551473943, 0.0953972529065, 0.136845820664, 0.120512364517, 0.119039243846, 0.140410360551, 0.108065133091, 0.137809748412, 0.117817032451, 0.152381073717, 0.11998529789, 0.130618014484, 0.124636729368, 0.110251736104, 0.119384827261, 0.0965530721291, 0.110701527379, 0.0798190699176, 0.108867796017, 0.0712493831641, 0.0965821570586, 0.0490329286169, 0.0829549792307, 0.0377052192845, 0.0624894607062, 0.0355988986848, 0.0461452853512, 0.0155302226258, 0.0390742176838, 0.0130573126748, 0.0321703373877, 0.0113348280728, 0.0291806755572, 0.00914507148247, 0.00965982248154, 0.0149652092267, 0.00525693954857, 0.00788690273152, 0.0103294864941, 0.00228337687758, -0.00159361272238, 0.0114922271955, 0.00114756032853, 0.00292951302251, 0.00495836391737, 0.000465547510033, 0.00254216918714, 0.00788396336875, -0.0036950665994, -0.00244756044469, -0.00614436126885, -0.00501508189525, -0.00585849138487, -0.00504161832473, -0.00803216337192, -0.0116683411929, -0.0104910799999, -0.0121011167546, -0.0176447697433, -0.0206587176768, -0.016395091962, -0.0147171477696, -0.0176591117544, -0.0155493986155, -0.00916109283029, -0.0114292846639, -0.00940178983247, -0.00674511114572}; // YOUR CODE HERE
float mean_vec[SNIPPET_SIZE] = {0.0021560029452, 0.00200365588558, 0.00262559056456, 0.00245728731905, 0.00270661423976, 0.00249029825067, 0.00288723722002, 0.00337888415481, 0.00441281558126, 0.00559185933893, 0.0105990196626, 0.00825813721634, 0.0112431335394, 0.0111341043344, 0.0116479422451, 0.0119480699055, 0.012059389953, 0.0117584985423, 0.0120587605417, 0.0113164988057, 0.010360557694, 0.0107252720123, 0.0106859685748, 0.00963212352964, 0.0101770886653, 0.0101216484612, 0.0101097761607, 0.0105915084735, 0.0103023903721, 0.0101098943757, 0.00985536057918, 0.00979547961116, 0.00880317683575, 0.00944088931067, 0.00814904877799, 0.00838420048164, 0.00792480133197, 0.00760453371638, 0.00798037270949, 0.00747269328127, 0.00799563105265, 0.0082783080638, 0.00910453294345, 0.00981107250136, 0.00927461836828, 0.00997066841121, 0.00930821997477, 0.0102406524701, 0.00965967728252, 0.0100115406161, 0.0103694255033, 0.00956293273933, 0.0100957172972, 0.00939309385133, 0.00978834525885, 0.009627653466, 0.00899208654139, 0.00973053158039, 0.00878207235859, 0.00945466321577, 0.00935810947466, 0.00991016158675, 0.01009182071, 0.00972801849565, 0.0101486286965, 0.00943017775235, 0.00966209994969, 0.00935236356733, 0.00932973024348, 0.00875757090134, 0.00922199138383, 0.00814739748944, 0.00855609936547, 0.00752164312371, 0.00857849537887, 0.00675396527281, 0.00841599667649, 0.00720523936148, 0.00806356143555, 0.00670339634711, 0.00817948080741, 0.00733498712704, 0.00778554773347, 0.00803920002513, 0.00754689036158, 0.00720121119831, 0.00729536946069, 0.00775835450249, 0.00713970932198, 0.0077017297494, 0.00772411758896, 0.00735881790642, 0.00742948961503, 0.00762663884547, 0.00742579358867, 0.00735868160112, 0.00752336317817, 0.00729553386806, 0.00796926097527, 0.00804205707846, 0.00798240424848, 0.00789396524814, 0.00835952029768, 0.00794706634572, 0.00817888639646, 0.0080499475568, 0.00832205291651, 0.00781060455402, 0.00819166338965, 0.00772365280431, 0.00829858422799, 0.00850321337086, 0.00782015297392, 0.00764568506787, 0.00740208479849, 0.00693050487365, 0.00714712516641, 0.00664046389275, 0.00603587826079, 0.00603181316666}; // YOUR CODE HERE
float centroid1[2] = {0.05064342,  0.05896214}; // YOUR CODE HERE
float centroid2[2] = {-0.00504472, -0.02667076}; // YOUR CODE HERE
float centroid3[2] = {-0.1,   0.00449142}; // YOUR CODE HERE
float centroid4[2] = {0.06098954, -0.04795757}; // YOUR CODE HERE
float result[SNIPPET_SIZE] = {0};
float proj1 = 0;
float proj2 = 0;
float dist[4] = {0};

/*----------------------*/
/* END OF CODE BLOCK A2 */
/*----------------------*/


//data array and index pointer
int i=0;
int re[SIZE]={0};
volatile int re_pointer = 0;

//timer period
float timer_ms = 0.35;

// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int*, float*);

// Compute the L2 norm of (dim1, dim2) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        centroid: size-2 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm(float dim1, float dim2, float* centroid){
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2));
}

// Compute the L2 norm of (dim1, dim2, dim3) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        dim3: 3rd dimension coordinate
//        centroid: size-3 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
//float l2_norm3(float dim1, float dim2, float dim3, float *centroid){
  //return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2), pow(dim3-centroid[2],2));
//}


void setup()
{
  //microphone ADC
  pinMode(MIC_INPUT, INPUT);
  pinMode(P6_1, INPUT);
  pinMode(P6_5, INPUT);
  //recording light
  pinMode(RED_LED, OUTPUT);

  re_pointer = 0;
  reset_blinker();
  setTimer();
  
  Serial.begin(38400); 
}



float PCAclassify(float data[], float basis[], float mean[]){
  float result = 0;
  for (i = 0; i < SNIPPET_SIZE; i ++) {
    result += (data[i]-mean[i])*basis[i];
  }
  return result;
}

int smallest(float array[]){
  float small = array[0];
  int index = 0;
  for (i =0; i<4; i ++) {
    if (small > array[i]) {
      small = array[i];
      index = i;
    }
  }
  return index;
}

float classify(float prj1, float prj2) {
  float dist4 = l2_norm(prj1, prj2, centroid1);
  float dist1 = l2_norm(prj1, prj2, centroid2);
  float dist3 = l2_norm(prj1, prj2, centroid3);
  float dist2 = l2_norm(prj1, prj2, centroid4);
  float things[4] = {dist1, dist2, dist3, dist4};
  int location = smallest(things);
  if (things[location] >KMEANS_THRESHOLD) {
    return -1;
  }
  else {
    return location+1;
  }
  
}

void findWord(int centroid) {
  if (centroid == 1) {
    Serial.println("okay");
  }
    if (centroid == 2) {
     Serial.println("hilfinger");
  }
    if (centroid == 3) {
      Serial.println("amor");
  }
    if (centroid == 4) {
      Serial.println("jazz");
  }
  else {
    Serial.println("try again bruh");  
  }
}

void loop()
{  
  if(re_pointer == SIZE){
    digitalWrite(RED_LED, LOW);
        Serial.println("bruh");  
        for (int i= 1; i < 5; i += 1) {
                  Serial.println(result[i]*1000);  
        }
    // Apply enveloping function and get snippet with speech. Do classification only if loud enough
    if(envelope(re, result)){
        Serial.println("h"); 
      /*--------------*/
      /* CODE BLOCK B */
      /*--------------*/

      // Perform principal component projection
      // YOUR CODE HERE 
      proj1 = PCAclassify(result, pca_vec1, mean_vec);
      proj2 = PCAclassify(result, pca_vec2, mean_vec);
      int centroid = classify(proj1, proj2);
              Serial.println(centroid); 
      findWord(centroid);
      // Classification - Hint: use the function l2_norm defined below
      // YOUR CODE HERE 
      
      /*---------------------*/
      /* END OF CODE BLOCK B */
      /*---------------------*/

    }
    
    delay(2000);
    re_pointer = 0;
  }
}


// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int* data, float* data_out){
  int32_t avg = 0;
  float maximum = 0;
  int thres_index = 0;
  int32_t total = 0;
  int block;

  // Apply enveloping filter while finding maximum value
  for (block = 0; block < SIZE_AFTER_FILTER; block++){
    avg = 0;
    for (int i = 0; i < 16; i++) {
      avg += data[i+block*16];
    }
    avg = avg >> 4;
    data[block] = abs(data[block*16] - avg);
    for (int i = 1; i < 16; i++) {
      data[block] += abs(data[i+block*16] - avg);
    }
    if (data[block] > maximum) {
      maximum = data[block];
    }
  }
  
  // If not loud enough, return false
  if (maximum < LOUDNESS_THRESHOLD) return false;

  // Determine threshold
  float thres = THRESHOLD * maximum;

  // Figure out when interesting snippet starts and write to data_out
  block = PRELENGTH;
  while (data[block++] < thres);
  if (block > SIZE_AFTER_FILTER - SNIPPET_SIZE) 
    block = SIZE_AFTER_FILTER - SNIPPET_SIZE;
  for (int i = 0; i < SNIPPET_SIZE; i++){
    data_out[i] = data[block-PRELENGTH+i];
    total += data_out[i];
  }

  // Normalize data_out 
  for (int i = 0; i < SNIPPET_SIZE; i++)
    data_out[i] = data_out[i] / total;

  return true;
}



// Timer ISR for ADC sampling
#pragma vector=TIMER0_A0_VECTOR    // Timer A ISR
__interrupt void Timer1_A0_ISR( void )
{
  if(re_pointer < SIZE){
    digitalWrite(RED_LED, HIGH);
    re[re_pointer] = (analogRead(MIC_INPUT) >> 4) - 128;
    re_pointer += 1;
  }
}

// Set timer for ADC
void setTimer(){
  // set the timer based on 25MHz clock
  TA0CCR0 = (unsigned int)(25000*timer_ms);       
  // enable interrupts for Timer A
  TA0CCTL0 = CCIE;             
  __bis_SR_register(GIE);
  TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_0;
}

void reset_blinker(){
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
}
