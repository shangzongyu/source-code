/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
const { start, dispatch, stop, spawn, spawnStateless } = require('nact');

const router = (module, state, msg, context) => {
  let action = module[msg.type];
  if (action && typeof (action) == "function") {
    const nextState = action(msg, context, state);
    return nextState !== undefined ? nextState : state;
  }
  else {
    console.log(`${context.name} customer ignores unknown message:`, msg);
    return state;
  }
}

const start_actor = (actors, name, module, initial_state={}) => {
    return spawn(actors,
                 (state, msg, context) => {
                   return router(module, state, msg, context)
                 },
                 name,
                 { initialState: initial_state }
    );
}


const sleep = (milliseconds) => {
  return new Promise(resolve => setTimeout(resolve, milliseconds))
}

////////////////////////////////////////////////////////////////////////////////////////

const pieCaseActor = {
  'get slice': (msg, context, state) => {
    if (state.slices.length == 0) {
      dispatch(msg.waiter,
               { type: 'error', msg: "no pie left", customer: msg.customer })
      return state
    }
    else {
      var slice = state.slices.shift() + " pie slice";
      dispatch(msg.customer,
               { type: 'put on table', food: slice });
      dispatch(msg.waiter,
               { type: 'add to order', food: slice, customer: msg.customer });
      return state;
    }
  }
}

const waiterActor = {
  "order": (msg, ctx, state) => {
    if (msg.wants == "pie") {
      dispatch(state.pieCase,
               { type: "get slice", customer: msg.customer, waiter: ctx.self })
    }
    else {
      console.dir(`Don't know how to order ${msg.wants}`);
    }
  },

  "add to order": (msg, ctx) =>
    console.log(`Waiter adds ${msg.food} to ${msg.customer.name}'s order`),

  "error": (msg, ctx) => {
    dispatch(msg.customer, { type: 'no pie left', msg: msg.msg });
    console.log(`\nThe waiter apologizes to ${msg.customer.name}: ${msg.msg}`)
  }

};

const customerActor = {
  'hungry for pie': (msg, ctx, state) => {
    return dispatch(state.waiter,
                    { type: "order", customer: ctx.self, wants: 'pie' })
  },

  'put on table': (msg, ctx, _state) =>
    console.log(`${ctx.self.name} sees "${msg.food}" appear on the table`),

  'no pie left': (_msg, ctx, _state) =>
    console.log(`${ctx.self.name} sulks…`)
}

/////////////////////////////////////////////////////////////////////////////////

const actorSystem = start();

let pieCase = start_actor(
  actorSystem,
  'pie-case',
  pieCaseActor,
  { slices: ["apple", "peach", "cherry"] });

let waiter = start_actor(
  actorSystem,
  'waiter',
  waiterActor,
  { pieCase: pieCase });

let c1 = start_actor(actorSystem,   'customer1',
                     customerActor, { waiter: waiter });
let c2 = start_actor(actorSystem,   'customer2',
                     customerActor, { waiter: waiter });

dispatch(c1, { type: 'hungry for pie', waiter: waiter });
dispatch(c2, { type: 'hungry for pie', waiter: waiter });
dispatch(c1, { type: 'hungry for pie', waiter: waiter });
dispatch(c2, { type: 'hungry for pie', waiter: waiter });
dispatch(c1, { type: 'hungry for pie', waiter: waiter });
sleep(500)
  .then(() => {
    stop(actorSystem);
  })
