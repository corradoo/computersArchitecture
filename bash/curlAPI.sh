curl -s $(curl -s https://api.thecatapi.com/v1/images/search?size=full | jq -r '.[0] .url') > kot;
catimg kot
curl -s http://api.icndb.com/jokes/random | jq '.value .joke'



