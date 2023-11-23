#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// want to represents vocab items by integers because then various tables
// need by the IBM model and EM training can just be represented as 2-dim
// tables indexed by integers

// the following #defines, defs of VS, VO, S, O, and create_vocab_and_data()
// are set up to deal with the specific case of the two pair corpus
// (la maison/the house)
// (la fleur/the flower)

// S VOCAB
#define LA 0
#define MAISON 1
#define FLEUR 2
// O VOCAB
#define THE 0
#define HOUSE 1
#define FLOWER 2

#define VS_SIZE 3
#define VO_SIZE 3
#define D_SIZE 2

vector<string> VS(VS_SIZE); // S vocab: VS[x] gives Src word coded by x
vector<string> VO(VO_SIZE); // O vocab: VO[x] gives Obs word coded by x

vector<vector<int> > S(D_SIZE); // all S sequences; in this case 2
vector<vector<int> > O(D_SIZE); // all O sequences; in this case 2

// sets S[0] and S[1] to be the int vecs representing the S sequences
// sets O[0] and O[1] to be the int vecs representing the O sequences
void create_vocab_and_data();

// functions which use VS and VO to 'decode' the int vecs representing the
// Src and Obs sequences
void show_pair(int d);
void show_O(int d);
void show_S(int d);

// displays results of each iteration
void iteration_results_display(int iter);

// padding string for output for ease of reading
string pad(string str);

// vectors for counts and trasnition probabilities intialisation
vector<vector<double> > counts(VO_SIZE, vector<double>(VS_SIZE));
vector<vector<double> > probs(VO_SIZE, vector<double>(VS_SIZE));

int main()
{
    create_vocab_and_data();
    // guts of it to go here
    // you may well though want to set up further global data structures
    // and functions which access them

    // calc starting probabilities
    for (int i = 0; i < VO_SIZE; i++)
    {
        for (int j = 0; j < VS_SIZE; j++)
        {
            probs[i][j] = 1 / (double)VS_SIZE;
        }
    }

    iteration_results_display(-1);

    for (int iter = 0; iter < 50; iter++)
    {
        // counts set to zero
        for (int i = 0; i < VO_SIZE; i++)
        {
            for (int j = 0; j < VS_SIZE; j++)
            {
                counts[i][j] = 0;
            }
        }

        // counts calcd
        for (int x = 0; x < D_SIZE; x++)
        {
            for (int i = 0; i < O[x].size(); i++)
            {
                // denom calc
                int o = O[x][i];
                double denomina = 0;
                for (int j = 0; j < S[x].size(); j++)
                {
                    int s = S[x][j];
                    denomina += probs[o][s];
                }
                for (int y = 0; y < S[x].size(); y++)
                {
                    int s = S[x][y];
                    counts[o][s] += probs[o][s] / denomina;
                }
            }
        }
        // probabilities calcd
        for (int i = 0; i < VS_SIZE; i++)
        {
            // calc demonima in (tr...) once
            double denomina = 0;
            for (int j = 0; j < VO_SIZE; j++)
            {
                denomina += counts[j][i];
            }
            for (int j = 0; j < VO_SIZE; j++)
            {
                probs[j][i] = counts[j][i] / denomina;
            }
        }
        iteration_results_display(iter);
    }
}

void create_vocab_and_data()
{

    VS[LA] = "la";
    VS[MAISON] = "maison";
    VS[FLEUR] = "fleur";

    VO[THE] = "the";
    VO[HOUSE] = "house";
    VO[FLOWER] = "flower";

    cout << "source vocab\n";
    for (int vi = 0; vi < VS.size(); vi++)
    {
        cout << VS[vi] << " ";
    }
    cout << endl;
    cout << "observed vocab\n";
    for (int vj = 0; vj < VO.size(); vj++)
    {
        cout << VO[vj] << " ";
    }
    cout << endl;

    // make S[0] be {LA,MAISON}
    //      O[0] be {THE,HOUSE}
    S[0] = {LA, MAISON};
    O[0] = {THE, HOUSE};

    // make S[1] be {LA,FLEUR}
    //      O[1] be {THE,FLOWER}
    S[1] = {LA, FLEUR};
    O[1] = {THE, FLOWER};

    for (int d = 0; d < S.size(); d++)
    {
        show_pair(d);
    }
}

void show_O(int d)
{
    for (int i = 0; i < O[d].size(); i++)
    {
        cout << VO[O[d][i]] << " ";
    }
}

void show_S(int d)
{
    for (int i = 0; i < S[d].size(); i++)
    {
        cout << VS[S[d][i]] << " ";
    }
}

void show_pair(int d)
{
    cout << "S" << d << ": ";
    show_S(d);
    cout << endl;
    cout << "O" << d << ": ";
    show_O(d);
    cout << endl;
}

void display_probs() {
    for(int i = 0; i< VO_SIZE; i++) {
        for(int j = 0; j < VS_SIZE; j++) {
            cout << VS[i] << '\t' << VO[j] << '\t';
            cout << probs[i][j];
            cout << endl;
        }
    }
}

void display_counts() {
    for(int i = 0; i< VO_SIZE; i++) {
        for(int j = 0; j < VS_SIZE; j++) {
            cout << VS[i] << '\t' << VO[j] << '\t';
            cout << counts[i][j];
            cout << endl;
        }
    }
}

void iteration_results_display(int iter)
{
  if(iter == -1) {
    cout << "initial trans probs are" << endl;
    return display_probs();
  }
  cout << "unnormalised counts in iteration " << iter << " are" << endl;
  display_counts();
  cout << "after iteration " << iter << " probs are" << endl;
  display_probs();
}