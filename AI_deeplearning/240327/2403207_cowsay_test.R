install.packages('cowsay')

library(cowsay)

say('Hello World!', by = 'cat')
say('좋은 아침', by = 'snowman')

say('고양이 귀여워', by = 'bigcat')
say('부엉이 귀여워', by = 'owl')


# Using fortunes
say(what="fortune")
## you don't have to pass anything to the `what` parameter if `fortune` is
## not null
say(fortune=10)
say(fortune=100)
say(fortune='whatever')
say(fortune=7)
say(fortune=45)

# Using catfacts
# say("catfact", "cat")

# The hypnotoad
say(by="hypnotoad")
